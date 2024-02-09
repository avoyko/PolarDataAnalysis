#pragma once

#include "utilities.h"
#include "request.h"

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
              client_secret_(client_secret) {};

    ~OAuth2Client() = default;

    Headers GetAuthHeaders(const std::string &access_token);

    std::string GetAuthorizationUrl(std::string response_type = "code");

    json GetAccessToken(const std::string &authorization_code);

    void PrepareRequest(Request &request_body, const std::string& access_token = "");

    static ParsedResponse ParseResponse(Response &response);

    template<typename ...CprRequestParameters>
    ParsedResponse Get(CprRequestParameters &&... parameters) {
        Response response = cpr::Get(std::forward<CprRequestParameters>(parameters)...);
        return ParseResponse(response);
    }

    template<typename ...CprRequestParameters>
    ParsedResponse Put(CprRequestParameters &&... parameters) {
        Response response = cpr::Put(std::forward<CprRequestParameters>(parameters)...);
        return ParseResponse(response);
    }

    template<typename ...CprRequestParameters>
    ParsedResponse Post(CprRequestParameters &&... parameters) {
        Response response = cpr::Post(std::forward<CprRequestParameters>(parameters)...);
        return ParseResponse(response);
    }

    template<typename ...CprRequestParameters>
    ParsedResponse Delete(CprRequestParameters &&... parameters) {
        Response response = cpr::Delete(std::forward<CprRequestParameters>(parameters)...);
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