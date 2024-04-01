#include "driver.h"

static AccessLink accesslink(Client::CLIENT_ID, Client::CLIENT_SECRET, Client::REDIRECT_URI);

int main() {
    crow::SimpleApp app;
    app.loglevel(crow::LogLevel::Info);
    ;
    CROW_ROUTE(app, "/")
    ([](const crow::request &req) {
        CROW_LOG_INFO << "Client is redirected for authorization";
        crow::response res{200};
        res.redirect(accesslink.GetAuthUrl());
        return res;
    });

    CROW_ROUTE(app, Callback::OAUTHPOINT)
    ([](const crow::request &req) {
        std::string authorization_code = req.url_params.get("code");
        rjson token_response = accesslink.GetAccessToken(authorization_code);
        std::string string_access_token = token_response["access_token"].s();
        YAML::Node config = YAML::LoadFile("../../config.yaml");
        config["user_id"] = std::to_string(token_response["x_user_id"].i());
        config["access_token"] = string_access_token;
        std::ofstream file_out("../../config.yaml");
        file_out << config;
        file_out.close();
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
    });

    CROW_ROUTE(app, Callback::DATAPOINT)
    ([](const crow::request &req) {
        YAML::Node config = YAML::LoadFile("../../config.yaml");
        ParsedResponse user_info = accesslink.GetUserdata(config["access_token"].as<std::string>(),
                                                          config["user_id"].as<std::string>());
        ParsedResponse exercises_info =
            accesslink.GetExercises(config["access_token"].as<std::string>());
        ParsedResponse activity_info;
        ParsedResponse phys_info;
        ParsedResponse sleep_info;
        //        DBWorker::UpdateDB({static_cast<wjson>(exercises_info),
        //        static_cast<wjson>(activity_info),
        //                            static_cast<wjson>(phys_info),
        //                            static_cast<wjson>(sleep_info)});
        DBWorker::UpdateDB({static_cast<wjson>(exercises_info), static_cast<wjson>(exercises_info),
                            static_cast<wjson>(exercises_info),
                            static_cast<wjson>(exercises_info)});
        model.work();
        crow::mustache::set_base("../../src/templates");
        auto page = crow::mustache::load("hello.html");
        return page.render(user_info);
    });
    CROW_LOG_INFO << "Navigate to http://localhost:5002/ to register user.";
    app.port(Callback::PORT).run();
}
