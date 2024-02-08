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

    Headers GetAuthHeaders(const std::string &access_token);

    std::string GetAuthorizationUrl(std::string response_type = "code");

    json GetAccessToken(const std::string &authorization_code);

    void PrepareRequest(Request &request_body);

    ParsedResponse ParseResponse(Response &response);

    template<class Method, typename ...CprRequestParameters>
    ParsedResponse ProcessRequest(Method method, CprRequestParameters &&... parameters);

    // TODO I changed only Post Functions, other in process

//    ParsedResponse Get(Request &request_body);
//
//    ParsedResponse Put(Request &request_body);

    template<typename ...CprRequestParameters>
    ParsedResponse Post(CprRequestParameters &&... parameters);

//    ParsedResponse Delete(Request &request_body);

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

// TODO I guess we don't need it anymore

template<class Method, typename ...CprRequestParameters>
ParsedResponse OAuth2Client::ProcessRequest(Method method, CprRequestParameters &&... parameters) {
    Response response = method.MakeRequest(std::forward<CprRequestParameters>(parameters)...);
    return ParseResponse(response);
}

//ParsedResponse OAuth2Client::Get(Request &request_body) {
//    return ProcessRequest(GetRequest(), request_body);
//}
//
//ParsedResponse OAuth2Client::Put(Request &request_body) {
//    return ProcessRequest(PutRequest(), request_body);
//}

template<typename ...CprRequestParameters>
ParsedResponse OAuth2Client::Post(CprRequestParameters &&... parameters) {
    return ProcessRequest(PostRequest(), std::forward<CprRequestParameters>(parameters)...);
}

//ParsedResponse OAuth2Client::Delete(Request &request_body) {
//    return ProcessRequest(DeleteRequest(), request_body);
//}