#include "oauth2.hpp"
#include <optional>

/// Problems:

/// 1. QueryArgs wrapper
/// 2. ParsedResponse type

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

json OAuth2Client::get_access_token(const std::string &authorization_code) {
    Headers headers = {{"Content-Type", "application/x-www-form-urlencoded"},
                       {"Accept",       "application/json;charset=UTF-8"}};

    boost::format fmt = boost::format(R"("grant_type" : "authorization_code", "code" : %1%)") %
                        authorization_code;
    Body data = {fmt.str()};

    auto response = post({Utils::EMPTY_ENDPOINT, {{"url", access_token_url_}}, headers, data, authorization_code});
    return json::parse("");
}

QueryArgs OAuth2Client::_build_endpoint(const std::string &endpoint, QueryArgs &kwargs) {
    if (!endpoint.empty()) {
        kwargs["url"] = url_ + endpoint;
    }
//    endpoint = Utils::EMPTY_ENDPOINT;
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

std::string OAuth2Client::_build_auth(QueryArgs &kwargs) {
    if (!kwargs.Contains("auth")) {
        Authentication auth = Authentication{client_id_, client_secret_, cpr::AuthMode::BASIC};
        std::string to_encode = auth.GetAuthString();
        kwargs["auth"] = "Basic " "YmQzYTc3YTQtMGVkYy00NGU1LTgxYTUtMzA5NjQ0ZjBmYzlhOmI4NTRhMGNhLTJhNzQtNGRkZS05MTk2LTBjMGIxYjYzMTEwZQ==";
    }
    return kwargs["auth"];
}

std::optional<ParsedResponse> OAuth2Client::parse_response(Response &response) {

    ParsedResponse answer{std::string()};

    if (response.status_code >= 400) {

        boost::format fmt =
                boost::format("%1% %2%: %3%") % response.status_code % response.reason % response.text;
        std::string message = fmt.str();
        throw cpr::Error(response.status_code, std::move(message));
    }

    if (response.status_code == 204) {
        return std::nullopt;
    }

    try {
        json response_json = json::parse(response.text);
        answer.emplace<1>(response_json);
        return answer;
    } catch (...) {  /// actually in python they catch value-error, i didnt find it:-)
        answer.emplace<0>(response.text);
        return answer;
    }
};

template<class Method>
std::optional<ParsedResponse> OAuth2Client::_request(Method method, const Request &request_body) {
    QueryArgs kwargs = request_body.GetParameters();
    kwargs = _build_endpoint(request_body.GetEndpoint(), kwargs);
    // Headers headers = _build_headers(kwargs);
    std::string auth_string = _build_auth(kwargs);
    Headers headers = request_body.CprHeader();
    Response response = method.MakeRequest(request_body.CprUrl(),
                                           cpr::Payload{{"grant_type", "authorization_code"},
                                                        {"code",       request_body.auto_code_}},
                                           headers,
                                           cpr::Authentication{client_id_, client_secret_, cpr::AuthMode::BASIC});
    return parse_response(response);
}

std::optional<ParsedResponse> OAuth2Client::get(const Request &request_body) {
    return _request(Get(), request_body);
}

std::optional<ParsedResponse> OAuth2Client::put(const Request &request_body) {
    return _request(Put(), request_body);
}

std::optional<ParsedResponse> OAuth2Client::post(const Request &request_body) {
    return _request(Post(), request_body);
}

std::optional<ParsedResponse> OAuth2Client::remove(const Request &request_body) {
    return _request(Delete(), request_body);
}