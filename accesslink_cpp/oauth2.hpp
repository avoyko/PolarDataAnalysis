#pragma once


#include "utils.hpp"

using json = nlohmann::json;
using Authentication = cpr::Authentication;
using Response = cpr::Response;
using Headers = cpr::Header;
using Body = cpr::Body;
using ParsedResponse = std::variant<std::string, json>;


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

    std::string get_authorization_url(const std::string &response_type);

    std::string get_access_code(const std::string &authorization_code);

    Parameters __build_endpoint(Parameters &kw);

    Headers __build_headers(Parameters &kw);

    std::string __build_auth(Parameters &kw);

    Parameters __build_request(Parameters &kw);

    ParsedResponse parse_response(Response &response);

    template <class Method>
    auto __request(Method method, Parameters &kw);

    auto get(std::string &endpoint, Parameters &kw);

    auto put(std::string &endpoint, Parameters &kw);

    auto post(std::string &endpoint, Parameters &kw);

    auto remove(std::string &endpoint, Parameters &kw);
    ~OAuth2Client() = default;

private:
    const std::string url_;
    const std::string authorization_url_;
    const std::string access_token_url_;
    const std::string redirect_url_;
    const std::string client_id_;
    const std::string client_secret_;
};
