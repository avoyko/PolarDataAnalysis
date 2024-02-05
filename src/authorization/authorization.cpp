#include "authorization.hpp"

#include <crow/app.h>
#include <crow/logging.h>
#include <cpr/error.h>
#include <cpr/cpr.h>
#include <cpr/parameters.h>

static AccessLink accesslink(Client::CLIENT_ID, Client::CLIENT_SECRET, Client::REDIRECT_URI);

int shutdown(crow::SimpleApp &app) {
    CROW_LOG_INFO << "Server is shutting down";
    app.stop();
    return 0;
}

void authorize() {
    Response response = cpr::Get(cpr::Url(Client::REDIRECT_URI));
    std::string authorization_code = json::parse(response.text)["code"];
    json token_response = accesslink.get_access_token(authorization_code);
    
       std::string user_id = token_response["x_user_id"];
       std::string access_token = token_response["access_token"];
    
       try {
           accesslink.register_user(access_token);
       } catch (...) {  /// it should be smth like exceptions.HTTPError
           throw;
       }

    CROW_LOG_INFO << "Client authorized! You can now close this page.";
}

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")
    ([](crow::response &response) {
        CROW_LOG_INFO << "Client is redirected for authorization";
        return response.redirect(Callback::OAUTHPOINT);
    });

    CROW_ROUTE(app, Callback::OAUTHPOINT)
    ([&app]() {
        authorize();
        return shutdown(app);
    });

    app.port(Callback::PORT).run();
}
