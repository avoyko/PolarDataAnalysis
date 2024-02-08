#include "authorization.hpp"

#include <crow/app.h>
#include <crow/logging.h>
#include <cpr/cpr.h>
#include "yaml-cpp/yaml.h"
#include <cpr/parameters.h>

static AccessLink accesslink(Client::CLIENT_ID, Client::CLIENT_SECRET, Client::REDIRECT_URI);

int shutdown(crow::SimpleApp &app) {
    CROW_LOG_INFO << "Server is shutting down";
    app.stop();
    return 0;
}

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")
            ([](const crow::request &req) {
                CROW_LOG_INFO << "Client is redirected for authorization";
                crow::response res{200};
                res.redirect(accesslink.GetAuthUrl());
                return res;
            });

    CROW_ROUTE(app, Callback::OAUTHPOINT)
            ([&app](const crow::request &req) {
                std::string authorization_code = req.url_params.get("code");
                json token_response = accesslink.GetAccessToken(authorization_code);
                std::string string_access_token = to_string(token_response["access_token"]);
                string_access_token = string_access_token.substr(1, string_access_token.size() - 2);
                YAML::Node config = YAML::LoadFile("../../config.yaml");
                config["user_id"] = to_string(token_response["x_user_id"]);
                config["access_token"] = string_access_token;
                std::ofstream file_out("../../config.yaml");
                file_out << config;
                file_out.close();
                try {
                    accesslink.RegisterUser(config["access_token"].as<std::string>());
                    CROW_LOG_INFO << "Successfully logged in";
                } catch (long exception_code) {
                    if (exception_code == 409) {
                        CROW_LOG_INFO << "User has been already registered";
                    }
                }
//                shutdown(app);
                CROW_LOG_INFO << "Client authorized! You can now close this page.";
                return crow::response{200};
            });

    app.port(Callback::PORT).run();
}
