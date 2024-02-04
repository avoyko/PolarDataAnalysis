#include "authorization.hpp"


static AccessLink accesslink(Client::CLIENT_ID, Client::CLIENT_SECRET, Client::REDIRECT_URI);


std::string authorize(){
    Response response;
    std::string authorization_code = cpr::Get("code").text;
    json token_response = accesslink.get_access_token(authorization_code);


    return "Client authorized! You can now close this page.";
}

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")
    ([](crow::response response) { return response.redirect(Callback::OAUTHPOINT); });

    CROW_ROUTE(app, Callback::OAUTHPOINT)
    ([]() { return authorize(); });

    app.port(Callback::PORT).run();
}
