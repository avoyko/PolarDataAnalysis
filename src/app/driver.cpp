#include "driver.h"
#include "../model/include/model.h"

static AccessLink accesslink(Client::CLIENT_ID, Client::CLIENT_SECRET, Client::REDIRECT_URI);

int PolarApp::Activate() {
    crow::SimpleApp app;
    app.loglevel(crow::LogLevel::Info);

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
    CROW_LOG_INFO << "Navigate to http://localhost:5002/ to register user.";
    app.port(Callback::PORT).run();
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
        CROW_LOG_INFO << "Successfully logged in!";
    } catch (long exception_code) {
        if (exception_code == 409) {
            CROW_LOG_INFO << "User has been already registered";
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

    Model model;
    model.Activate();

    crow::mustache::set_base("../../src/templates");
    auto page = crow::mustache::load("hello.html");
    return page.render(user_info);
}
