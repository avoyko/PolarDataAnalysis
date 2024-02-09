#include "oauth2.h"


Headers OAuth2Client::GetAuthHeaders(const std::string &access_token) {
    Headers headers{{"Authorization", "Bearer " + access_token},
                    {"Content-Type",  "application/json"},
                    {"Accept",        "application/json"}};
    return headers;
}

std::string OAuth2Client::GetAuthorizationUrl(const std::string response_type) {
    Parameters params{{"client_id",     client_id_},
                      {"response_type", response_type}};
    boost::format fmt = boost::format("%1%?%2%") % authorization_url_ % params.GetContent(cpr::CurlHolder());
    return fmt.str();
}

ParsedResponse OAuth2Client::GetAccessToken(const std::string &authorization_code) {
    Headers headers = {{"Content-Type", "application/x-www-form-urlencoded"},
                       {"Accept",       "application/json;charset=UTF-8"}};

    Parameters payload{{"grant_type", "authorization_code"},
                       {"code",       authorization_code}};

    Request request_body{Utils::EMPTY_ENDPOINT, payload, headers};
    PrepareRequest(request_body); // Now we prepare it here
    return Post(request_body.CprUrl(), request_body.CprParameters(), request_body.CprHeader(),
                cpr::Authentication{client_id_, client_secret_, cpr::AuthMode::BASIC});
}


void OAuth2Client::PrepareRequest(Request &request_body, const std::string &access_token) {
    if (access_token.empty()) {
        request_body.UpdateUrl(access_token_url_);
    } else {
        Headers auth_headers = GetAuthHeaders(access_token);
        request_body.UpdateHeaders(auth_headers);
        request_body.UpdateUrl(url_ + request_body.GetEndpoint());
    }
}


ParsedResponse OAuth2Client::ParseResponse(Response &response) {
    if (response.status_code >= 400) {
//        boost::format fmt =
//                boost::format("%1% %2%: %3%") % response.status_code % response.reason % response.text;
//        std::string message = fmt.str();
//        throw cpr::Error(response.status_code, std::move(message));
        throw response.status_code;
    }

    if (response.status_code == 204) {
        return {};
    }

    try {
        json response_json = json::parse(response.text);
        return response_json;
    } catch (const json::exception &error) {
        return {{"error", error.id}};
    }
};

