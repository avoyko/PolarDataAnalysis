#pragma once

#include "utilities.hpp"
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

    Headers get_auth_headers(const std::string &access_token);

    std::string get_authorization_url(std::string response_type = "code");

    json get_access_token(const std::string &authorization_code);

    void prepare_request(Request &request_body);

    ParsedResponse parse_response(Response &response);

    template<class Method>
    ParsedResponse _request(Method method, Request &request_body);

    ParsedResponse get(Request &request_body);

    ParsedResponse put(Request &request_body);

    ParsedResponse post(Request &request_body);

    ParsedResponse remove(Request &request_body);

    ~OAuth2Client() = default;

    /// how about creating wrapper of request args???

private:
    const std::string url_;
    const std::string authorization_url_;
    const std::string access_token_url_;
    const std::string redirect_url_;
    const std::string client_id_;
    const std::string client_secret_;
};
