#include "../include/oauth2.h"

cpr::Header OAuth2Client::GetAuthHeaders(const std::string &access_token) {
    cpr::Header headers{{"Authorization", "Bearer " + access_token},
                        {"Content-Type", "application/json"},
                        {"Accept", "application/json"}};
    return headers;
}

std::string OAuth2Client::GetAuthorizationUrl(const std::string response_type) {
    cpr::Parameters params{{"client_id", client_id_}, {"response_type", response_type}};
    boost::format fmt =
        boost::format("%1%?%2%") % authorization_url_ % params.GetContent(cpr::CurlHolder());
    return fmt.str();
}

ReadJson OAuth2Client::GetAccessToken(const std::string &authorization_code) {
    cpr::Header headers = {{"Content-Type", "application/x-www-form-urlencoded"},
                           {"Accept", "application/json;charset=UTF-8"}};

    cpr::Parameters payload{{"grant_type", "authorization_code"}, {"code", authorization_code}};

    RequestWrapper request_body{"", payload, headers};
    PrepareRequest(request_body);  // Now we prepare it here
    return Post(request_body.CprUrl(), request_body.CprParameters(), request_body.CprHeader(),
                cpr::Authentication{client_id_, client_secret_, cpr::AuthMode::BASIC});
}

void OAuth2Client::PrepareRequest(RequestWrapper &request_body, const std::string &access_token) {
    if (access_token.empty()) {
        request_body.UpdateUrl(access_token_url_);
    } else {
        cpr::Header auth_headers = GetAuthHeaders(access_token);
        request_body.UpdateHeaders(auth_headers);
        if (request_body.GetEndpoint().starts_with(url_)) {
            request_body.UpdateUrl(request_body.GetEndpoint());
        } else {
            request_body.UpdateUrl(url_ + request_body.GetEndpoint());
        }
    }
}

ReadJson OAuth2Client::ParseResponse(cpr::Response &response) {
    if (response.status_code >= 400) {
        throw response.status_code;
    }
    if (response.status_code == 204) {
        return {};
    }
   // std::cout << response.text << std::endl;
    return crow::json::load(response.text);
};
