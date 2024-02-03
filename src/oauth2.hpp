#pragma once

#include "utilities.hpp"

using json = nlohmann::json;
using ParsedResponse = std::variant<std::string, json>;
using Authentication = cpr::Authentication;
using Response = cpr::Response;
using Headers = cpr::Header;
using Body = cpr::Body;

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

    std::string get_authorization_url(const std::string response_type = "code");

    std::string get_access_token(const std::string &authorization_code);

    QueryArgs __build_endpoint(QueryArgs &kwargs);

    Headers __build_headers(QueryArgs &kwargs);

    std::string __build_auth(QueryArgs &kwargs);

    QueryArgs __build_request(QueryArgs &kwargs);

    std::optional<ParsedResponse> parse_response(Response &response);

    template <class Method>
    std::optional<ParsedResponse> __request(Method method, QueryArgs &kwargs);

    std::optional<ParsedResponse> get(std::string endpoint, QueryArgs kwargs);

    std::optional<ParsedResponse> put(std::string &endpoint, QueryArgs kwargs);

    std::optional<ParsedResponse> post(std::string &endpoint, QueryArgs kwargs);

    std::optional<ParsedResponse> remove(std::string &endpoint, QueryArgs kwargs);
    ~OAuth2Client() = default;

private:
    const std::string url_;
    const std::string authorization_url_;
    const std::string access_token_url_;
    const std::string redirect_url_;
    const std::string client_id_;
    const std::string client_secret_;
};
