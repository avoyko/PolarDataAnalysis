#include "authorization.hpp"

#include <crow/app.h>
#include <crow/logging.h>
#include <cpr/error.h>
#include <cpr/cpr.h>
#include "yaml-cpp/yaml.h"
#include <cpr/parameters.h>
#include <iostream>

static AccessLink accesslink(Client::CLIENT_ID, Client::CLIENT_SECRET, Client::REDIRECT_URI);

//int shutdown(crow::SimpleApp &app) {
//    CROW_LOG_INFO << "Server is shutting down";
//    app.stop();
//    return 0;
//}

void authorize() {
//    Response response = cpr::Get(cpr::Url(Links::AUTHORIZATION_URL));
//    std::string authorization_code = json::parse(response.text)["code"];
//    json token_response = accesslink.get_access_token(authorization_code);
//
//    std::string user_id = token_response["x_user_id"];
//    std::string access_token = token_response["access_token"];
//
//    try {
//        accesslink.register_user(access_token);
//    } catch (...) {  /// it should be smth like exceptions.HTTPError
//        throw;
//    }


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
            ([](const crow::request &req) {
                std::string authorization_code = req.url_params.get("code");
                auto token_response = accesslink.GetAccessToken(authorization_code);
                CROW_LOG_INFO << "Client authorized! You can now close this page.";
                return crow::response{200};
            });

    app.port(Callback::PORT).run();
}
