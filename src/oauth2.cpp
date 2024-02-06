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

    auto response = post({Utils::EMPTY_ENDPOINT, payload, headers, authorization_code});
    return response;
}

QueryArgs OAuth2Client::_build_endpoint(const std::string &endpoint, QueryArgs &kwargs) {

    kwargs["url"] = url_ + endpoint;

    return kwargs;
}

Headers OAuth2Client::_build_headers(QueryArgs &kwargs) {
    Headers headers;
    if (kwargs.Contains("access_token")) {
        headers = get_auth_headers(kwargs["access_token"]);
        kwargs.Erase("access_token");
    }
    return headers;
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
ParsedResponse OAuth2Client::_request(Method method, const Request &request_body) {
    QueryArgs kwargs = request_body.GetParameters();
    kwargs = _build_endpoint(request_body.GetEndpoint(), kwargs);
    Headers headers = _build_headers(kwargs);
    Response response = method.MakeRequest(request_body.CprUrl(),
                                           request_body.CprParameters(),
                                           request_body.CprHeader(),
                                           cpr::Authentication{client_id_, client_secret_, cpr::AuthMode::BASIC});
    return parse_response(response);
}

ParsedResponse OAuth2Client::get(const Request &request_body) {
    return _request(Get(), request_body);
}

ParsedResponse OAuth2Client::put(const Request &request_body) {
    return _request(Put(), request_body);
}

ParsedResponse OAuth2Client::post(const Request &request_body) {
    return _request(Post(), request_body);
}

ParsedResponse OAuth2Client::remove(const Request &request_body) {
    return _request(Delete(), request_body);
}