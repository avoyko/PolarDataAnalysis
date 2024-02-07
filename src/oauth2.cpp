#include "oauth2.hpp"


Headers OAuth2Client::get_auth_headers(const std::string &access_token) {
    Headers headers{{"Authorization", "Bearer " + access_token},
                    {"Content-Type",  "application/json"},
                    {"Accept",        "application/json"}};
    return headers;
}

std::string OAuth2Client::get_authorization_url(const std::string response_type) {
    QueryArgs params{{"client_id",     client_id_},
                     {"response_type", response_type}};
    if (!redirect_url_.empty()) {
        params.Add({"redirect_uri", redirect_url_});
    }

    boost::format fmt = boost::format("%1%?%2%") % authorization_url_ % params.UrlEncode();
    return fmt.str();
}

ParsedResponse OAuth2Client::get_access_token(const std::string &authorization_code) {
    Headers headers = {{"Content-Type", "application/x-www-form-urlencoded"},
                       {"Accept",       "application/json;charset=UTF-8"}};

    QueryArgs payload{{"grant_type", "authorization_code"},
                      {"code",       authorization_code},
                      {"url",        access_token_url_}};
    Request request_body{Utils::EMPTY_ENDPOINT, payload, headers, authorization_code};
    auto response = post(request_body);
    return response;
}


void OAuth2Client::prepare_request(Request &request_body) {
    request_body.UpdateUrl(url_ + request_body.GetEndpoint());
    if (request_body.ContainsParameter("access_token")) {
        Headers auth_headers = get_auth_headers(request_body.GetParameter("access_token"));
        request_body.UpdateHeaders(auth_headers);
        request_body.RemoveParameter("access_token");
    }
}


ParsedResponse OAuth2Client::parse_response(Response &response) {

    if (response.status_code >= 400) {
        boost::format fmt =
                boost::format("%1% %2%: %3%") % response.status_code % response.reason % response.text;
        std::string message = fmt.str();
        throw cpr::Error(response.status_code, std::move(message));
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

template<class Method>
ParsedResponse OAuth2Client::_request(Method method, Request &request_body) {
    prepare_request(request_body);
    Response response = method.MakeRequest(request_body.CprUrl(),
                                           request_body.CprParameters(),
                                           request_body.CprHeader(),
                                           cpr::Authentication{client_id_, client_secret_, cpr::AuthMode::BASIC});
    return parse_response(response);
}

ParsedResponse OAuth2Client::get(Request &request_body) {
    return _request(Get(), request_body);
}

ParsedResponse OAuth2Client::put(Request &request_body) {
    return _request(Put(), request_body);
}

ParsedResponse OAuth2Client::post(Request &request_body) {
    return _request(Post(), request_body);
}

ParsedResponse OAuth2Client::remove(Request &request_body) {
    return _request(Delete(), request_body);
}