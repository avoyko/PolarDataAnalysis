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
          client_secret_(client_secret){};

    Headers get_auth_headers(const std::string &access_token);

    std::string get_authorization_url(std::string response_type = "code");

    json get_access_token(const std::string &authorization_code);

    QueryArgs _build_endpoint(std::string& endpoint, QueryArgs &kwargs);

    Headers _build_headers(QueryArgs &kwargs);

    std::string _build_auth(QueryArgs &kwargs);

    std::optional<ParsedResponse> parse_response(Response &response);

    template <class Method>
    std::optional<ParsedResponse> _request(Method method, const Request &request_body);

    std::optional<ParsedResponse> get(const Request &request_body);

    std::optional<ParsedResponse> put(const Request &request_body);

    std::optional<ParsedResponse> post(const Request &request_body);

    std::optional<ParsedResponse> remove(const Request &request_body);
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
