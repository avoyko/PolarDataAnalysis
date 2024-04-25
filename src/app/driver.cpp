#include "driver.h"
#include "../gui.h"
#include "../model/include/model.h"
#include "../calendar_scheduler/include/scheduler.h"

#include <fstream>
#include <iostream>

static AccessLink accesslink(Client::CLIENT_ID, Client::CLIENT_SECRET, Client::REDIRECT_URI);

ScreenConfig screen_config;

class CustomLogger : public crow::ILogHandler {
public:
    CustomLogger() : logs_("../../log/crow_logs.txt") {};

    void log(std::string message, crow::LogLevel) override {
        logs_ << message << std::endl;
    }

private:
    std::ofstream logs_;
};

int PolarApp::Activate() {
    CustomLogger logger;
    crow::logger::setHandler(&logger);

    crow::SimpleApp app;

    InitialiseStartScreen(screen_config);
    InitialiseMainWindow(screen_config);

    CROW_ROUTE(app, "/")
            ([](const crow::request &req) {
                CROW_LOG_INFO << "Client is redirected for authorization";
                crow::response res{200};
                res.redirect(accesslink.GetAuthUrl());
                return res;
            });

    CROW_ROUTE(app, Callback::OAUTHPOINT)
            ([this](const crow::request &req) { return Authorize(req); });

    CROW_ROUTE(app, Callback::DATAPOINT)
            ([this](const crow::request &req) { return ProcessData(); });

#if (DEVELOPER_MODE == 1)
    CROW_LOG_INFO << "Navigate to http://localhost:5002/ to register user.";
#else
    CROW_LOG_INFO << "Navigate to http://172.17.0.2:5002/ to register user.";
#endif
    app.port(Callback::PORT).run();

    delwin(screen_config.main_window);
    endwin();
    return 0;
}

YAML::Node PolarApp::UpdateAccessConfig(const ReadJson &token_response) {
    std::string string_access_token = token_response["access_token"].s();
    YAML::Node config = YAML::LoadFile("../../config.yaml");
    config["user_id"] = std::to_string(token_response["x_user_id"].i());
    config["access_token"] = string_access_token;
    std::ofstream file_out("../../config.yaml");
    file_out << config;
    file_out.close();
    return config;
}

crow::response PolarApp::Authorize(const crow::request &req) {
    std::string authorization_code = req.url_params.get("code");
    ReadJson token_response = accesslink.GetAccessToken(authorization_code);
    YAML::Node config = UpdateAccessConfig(token_response);
    try {
        accesslink.RegisterUser(config["access_token"].as<std::string>());
        std::string login_message = "Successfully logged in!";
        CROW_LOG_INFO << login_message;
        mvwprintw(screen_config.main_window, screen_config.windowHeight / 2,
                  (screen_config.windowWidth - login_message.size()) / 2,
                  login_message.c_str());
        wrefresh(screen_config.main_window);
    } catch (long exception_code) {
        if (exception_code == 409) {
            std::string login_message = "User has been already registered";
            CROW_LOG_INFO << login_message;
            mvwprintw(screen_config.main_window, screen_config.windowHeight / 2,
                      (screen_config.windowWidth - login_message.size()) / 2,
                      login_message.c_str());
            wrefresh(screen_config.main_window);
        }
    }
    crow::response res{200};
    res.redirect(Client::DATA_URI);
    return res;
}

crow::mustache::rendered_template PolarApp::ProcessData() {
    YAML::Node config = YAML::LoadFile("../../config.yaml");
    const auto access_token = config["access_token"].as<std::string>();
    const auto user_id = config["user_id"].as<std::string>();

    WriteJson user_info = accesslink.GetUserdata(access_token, user_id);
    WriteJson exercises_info = accesslink.GetExercises(access_token, user_id);
    WriteJson activity_info = accesslink.GetActivity(access_token, user_id);
    WriteJson phys_info = accesslink.GetPhysicalInfo(access_token, user_id);
    WriteJson sleep_info = accesslink.GetSleep(access_token, user_id);

    DBWorker &db_worker = DBWorker::GetInstance();
    db_worker.UpdateDB({exercises_info, activity_info, phys_info, sleep_info});

    InitialiseOptionPanel(screen_config);
    auto options = ActivateOptionsScreen(screen_config);

    Model model;
    model.Activate();
    std::vector<std::string> event_names = model.GetPrediction();

    CalendarClient calendarClient;
    calendarClient.ScheduleEvents(event_names);

    crow::mustache::set_base("../../src/templates");
    auto page = crow::mustache::load("hello.html");
    return page.render(user_info);
}
