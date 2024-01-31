#include "oauth2.hpp"


Headers OAuth2Client::get_auth_headers(const std::string &access_token) {
    Headers headers{{"Authorization", "Bearer " + access_token},
                    {"Content-Type", "application/json"},
                    {"Accept", "application/json"}};
    return headers;
}

std::string OAuth2Client::get_authorization_url(const std::string &response_type) {
    Parameters params{{"client_id", client_id_}, {"response_type", response_type}};
    if (!redirect_url_.empty()) {
        params.Add({"redirect_uri", redirect_url_});
    }

    boost::format fmt = boost::format("%1?%2") % authorization_url_ % params.UrlEncode();
    return fmt.str();
}

std::string OAuth2Client::get_access_code(const std::string &authorization_code) {
    Headers headers = {{"Content-Type", "application/x-www-form-urlencoded"},
                       {"Accept", "application/json;charset=UTF-8"}};

    Body data = {R"(
            {"grant_type" : "authorization_code",
            "code" : authorization_code})"};  /// need to fix the "Unused parameter warning"

    Response response = cpr::Post(cpr::Url(access_token_url_), data, headers);
    return response.text;
}

Parameters OAuth2Client::__build_endpoint(Parameters &kw) {
    if (kw.IsNone("endpoint")) {
        if (!kw["endpoint"].empty()) {
            kw["url"] = url_ + kw["endpoints"];
        }
        kw.Erase("endpoint");
    }
    return kw;
}

Headers OAuth2Client::__build_headers(Parameters &kw) {
    Headers headers;
    if (kw.Contains("access_token")) {
        headers = get_auth_headers(kw["access_token"]);
        kw.Erase("access_token");
    }
    return headers;
}

std::string OAuth2Client::__build_auth(Parameters &kw) {
    Authentication auth = Authentication{"", "", cpr::AuthMode::BASIC};
    if (!kw.Contains("auth")) {  /// i should store Authentication obj???
        auth = Authentication{client_id_, client_secret_, cpr::AuthMode::BASIC};
        kw["auth"] = auth.GetAuthString();
    }
    return kw["auth"];
}

ParsedResponse OAuth2Client::parse_response(Response &response) {

    ParsedResponse answer{std::string()};

    if (response.status_code >= 400) {
        boost::format fmt =
            boost::format("%1 %2: %3") % response.status_code % response.reason % response.text;
        std::string message = fmt.str();
        throw cpr::Error(response.status_code, std::move(message));
    }

    if (response.status_code == 204) {
        return answer;  /// not sure, need details
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

template <class Method>
auto OAuth2Client::__request(Method method, Parameters &kw) {
    kw = __build_endpoint(kw);
    Headers headers = __build_headers(kw);
    std::string auth_string = __build_auth(kw);  /// need to think
    Response response = method.Request(kw);
    return parse_response(response);
}

auto OAuth2Client::get(std::string &endpoint, Parameters &kw) {
    return __request(Get(), kw.Add({"endpoint", endpoint}));
}

auto OAuth2Client::put(std::string &endpoint, Parameters &kw) {
    return __request(Put(), kw.Add({"endpoint", endpoint}));
}

auto OAuth2Client::post(std::string &endpoint, Parameters &kw) {
    return __request(Post(), kw.Add({"endpoint", endpoint}));
}

auto OAuth2Client::remove(std::string &endpoint, Parameters &kw) {
    return __request(Delete(), kw.Add({"endpoint", endpoint}));
}