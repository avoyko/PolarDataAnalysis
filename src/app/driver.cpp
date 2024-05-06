#include "driver.h"
#include "../gui.h"
#include "../model/include/model.h"
#include "../calendar_scheduler/include/scheduler.h"

#include <fstream>
#include <iostream>
#include <thread>


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

    CROW_ROUTE(app, Callback::WAITPOINT)
    ([this](const crow::request &req) { return Poll(); });

    CROW_LOG_INFO << "Navigate to http://localhost:5002/ to register user.";

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
    config["first_run"] = 1;
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
        mvwprintw(screen_config.main_window, screen_config.windowHeight / 4 + 2,
                  (screen_config.windowWidth - login_message.size()) / 2,
                  login_message.c_str());
        wrefresh(screen_config.main_window);
    } catch (long exception_code) {
        if (exception_code == 409) {
            std::string login_message = "User has been already registered";
            CROW_LOG_INFO << login_message;
            mvwprintw(screen_config.main_window, screen_config.windowHeight / 4 + 2,
                      (screen_config.windowWidth - login_message.size()) / 2,
                      login_message.c_str());
            wrefresh(screen_config.main_window);
        }
    }
    crow::response res{200};
    res.redirect(Client::DATA_URI);
    return res;
}

crow::response PolarApp::ProcessData() {
    YAML::Node config = YAML::LoadFile("../../config.yaml");
    const auto access_token = config["access_token"].as<std::string>();
    const auto user_id = config["user_id"].as<std::string>();

    std::vector<bool> options(2, false);
    if (config["first_run"].as<int>() == 1) {
        InitialiseOptionPanel(screen_config);
        options = ActivateOptionsScreen(screen_config);
        config["first_run"] = 0;
        std::ofstream file_out("../../config.yaml");
        file_out << config;
        file_out.close();
    } else {
        options[0] = true;
    }

    ClearBox(screen_config);

    WriteJson user_info = accesslink.GetUserdata(access_token, user_id);
    WriteJson exercises_info = accesslink.GetExercises(access_token, user_id);
    WriteJson activity_info = accesslink.GetActivity(access_token, user_id);
    WriteJson phys_info = accesslink.GetPhysicalInfo(access_token, user_id);
    WriteJson sleep_info = accesslink.GetSleep(access_token, user_id);

    DBWorker &db_worker = DBWorker::GetInstance();
    db_worker.UpdateDB({exercises_info, activity_info, phys_info, sleep_info});

    if (options[0]) {
        Model model;
        std::atomic_bool model_finished = false;

        std::thread waiting_panel(DisplayLoadingPanel, std::cref(screen_config), std::cref(model_finished));
        model.Activate();

        std::vector<std::string> event_names = model.GetPrediction();

        model_finished = true;
        waiting_panel.join();

        std::string finish_message = "Model has finished";
        mvwprintw(screen_config.main_window, screen_config.windowHeight / 4,
                  (screen_config.windowWidth - finish_message.size()) / 2,
                  finish_message.c_str());
        wrefresh(screen_config.main_window);

        CalendarClient calendarClient;
        calendarClient.ScheduleEvents(event_names);

        std::string goodbye_message = "Events for the next day are scheduled";
        mvwprintw(screen_config.main_window, screen_config.windowHeight / 4 + 2,
                  (screen_config.windowWidth - goodbye_message.size()) / 2,
                  goodbye_message.c_str());
        wrefresh(screen_config.main_window);
    } else {
        delwin(screen_config.main_window);
        endwin();
        exit(0);
    }

    crow::response res{200};
    res.redirect(Client::WAIT_URI);
    return res;
}

crow::response PolarApp::Poll() {
    int cur_hour = -1;
    while (cur_hour != 1) { // will upload in 1am
        auto current_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        auto local_time = *std::localtime(&current_time);
        cur_hour = local_time.tm_hour;
    }
    crow::response res{200};
    res.redirect(Client::DATA_URI);
    return res; // go to model section
}