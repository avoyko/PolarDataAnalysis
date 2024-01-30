#pragma once

#include <boost/format/format_fwd.hpp>
#include <nlohmann/json_fwd.hpp>
#include <cpr/error.h>
#include <cpr/parameters.h>
#include <cpr/cpr.h>
#include <cpr/response.h>
#include <nlohmann/json.hpp>
#include <boost/format.hpp>
#include <variant>
#include "cpr/api.h"
#include "cpr/auth.h"
#include "cpr/body.h"
#include "cpr/cprtypes.h"
#include "cpr/curlholder.h"
#include "cpr/payload.h"
#include "utils.hpp"

using json = nlohmann::json;
using cpr::Authentication;
using cpr::Response;
using ParsedResponse = std::variant<std::string, json>;
using Headers = Parameters;

class OAuth2Client {
public:
    OAuth2Client(std::string_view url, std::string_view authorization_url,
                 std::string_view access_token_url, std::string_view redirect_url,
                 std::string_view client_id, std::string_view client_secret)
        : url_(url),
          authorization_url_(authorization_url),
          access_token_url_(access_token_url),
          redirect_url_(redirect_url),
          client_id_(client_id),
          client_secret_(client_secret){};

    Parameters get_auth_headers(const std::string &access_token) {
        Parameters headers{{"Authorization", "Bearer " + access_token},
                           {"Content-Type", "application/json"},
                           {"Accept", "application/json"}};
        return headers;
    }

    std::string get_authorization_url(const std::string &response_type) {
        Parameters params{{"client_id", client_id_}, {"response_type", response_type}};
        if (!redirect_url_.empty()) {
            params.Add({"redirect_uri", redirect_url_});
        }

        boost::format fmt = boost::format("%1?%2") % authorization_url_ % params.UrlEncode();
        return fmt.str();
    }

    std::string get_access_code(const std::string &authorization_code) {
        cpr::Header headers = {{"Content-Type", "application/x-www-form-urlencoded"},
                           {"Accept", "application/json;charset=UTF-8"}};

        cpr::Body data = {R"(
            {"grant_type" : "authorization_code",
            "code" : authorization_code})"};   ///need to fix the "Unused parameter warning"

        cpr::Response response = cpr::Post(cpr::Url(access_token_url_), data, headers);
        return response.text;
    }

    Parameters __build_endpoint(Parameters &kw) {
        if (kw.IsNone("endpoint")) {
            if (!kw["endpoint"].empty()) {
                kw["url"] = url_ + kw["endpoints"];
            }
            kw.Erase("endpoint");
        }
        return kw;
    }

    Headers __build_headers(Parameters &kw) {
        Headers headers;
        if (kw.Contains("access_token")) {
            headers = get_auth_headers(kw["access_token"]);
            kw.Erase("access_token");
        }
        return headers;
    }

    Authentication __build_auth(Parameters &kw) {
        /// probably i will create yet another wrapper for Authentication
        /// because i wish i could have empty object (i need empty ctor)
        Authentication auth = cpr::Authentication{"", "", cpr::AuthMode::BASIC};
        if (!kw.Contains("auth")) {
            kw["auth"] = "authentication complete";
            auth = cpr::Authentication{client_id_, client_secret_, cpr::AuthMode::BASIC};
        }
        return auth;
    }

    Parameters __build_request(Parameters &kw) {
        kw = __build_endpoint(kw);
        Headers headers = __build_headers(kw);
        Authentication auth = __build_auth(kw);
        return kw;
    }

    ParsedResponse parse_response(Response &response) {

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

    auto __request(std::string method, Parameters &kw) {
        kw = __build_request(kw);
        Headers headers = __build_headers(kw);
        Authentication auth = __build_auth(kw);
        Response response;
        method = "";  // must be something with request i guess
        return parse_response(response);
    }

    auto get(std::string &endpoint, Parameters &kw) {
        return __request("get", kw.Add({"endpoint", endpoint}));
    }

    auto put(std::string &endpoint, Parameters &kw) {
        return __request("put", kw.Add({"endpoint", endpoint}));
    }

    auto post(std::string &endpoint, Parameters &kw) {
        return __request("post", kw.Add({"endpoint", endpoint}));
    }

    auto remove(std::string &endpoint, Parameters &kw) {
        cpr::Post();
        return __request("delete", kw.Add({"endpoint", endpoint}));
    }
    ~OAuth2Client() = default;

private:
    const std::string url_;
    const std::string authorization_url_;
    const std::string access_token_url_;
    const std::string redirect_url_;
    const std::string client_id_;
    const std::string client_secret_;
};
