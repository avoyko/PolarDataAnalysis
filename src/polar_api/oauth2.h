#pragma once

#include <boost/format.hpp>
#include <crow/json.h>
#include "request_wrap.h"

using ReadJson = crow::json::rvalue;
using WriteJson = crow::json::wvalue;

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

    ~OAuth2Client() = default;

    cpr::Header GetAuthHeaders(const std::string &access_token);

    std::string GetAuthorizationUrl(std::string response_type = "code");

    ReadJson GetAccessToken(const std::string &authorization_code);

    void PrepareRequest(RequestWrapper &request_body, const std::string &access_token = "");

    ReadJson ParseResponse(cpr::Response &response);

    template <typename... CprRequestParameters>
    ReadJson Get(CprRequestParameters &&...parameters) {
        cpr::Response response = cpr::Get(std::forward<CprRequestParameters>(parameters)...);
        return ParseResponse(response);
    }

    template <typename... CprRequestParameters>
    ReadJson Put(CprRequestParameters &&...parameters) {
        cpr::Response response = cpr::Put(std::forward<CprRequestParameters>(parameters)...);
        return ParseResponse(response);
    }

    template <typename... CprRequestParameters>
    ReadJson Post(CprRequestParameters &&...parameters) {
        cpr::Response response = cpr::Post(std::forward<CprRequestParameters>(parameters)...);
        return ParseResponse(response);
    }

    template <typename... CprRequestParameters>
    ReadJson Delete(CprRequestParameters &&...parameters) {
        cpr::Response response = cpr::Delete(std::forward<CprRequestParameters>(parameters)...);
        return ParseResponse(response);
    }

private:
    const std::string url_;
    const std::string authorization_url_;
    const std::string access_token_url_;
    const std::string redirect_url_;
    const std::string client_id_;
    const std::string client_secret_;
};