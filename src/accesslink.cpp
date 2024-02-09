#include "accesslink.h"

std::string AccessLink::GetAuthUrl() {
    return oauth_.GetAuthorizationUrl();
}

json AccessLink::GetAccessToken(const std::string &authorization_code) {
    return oauth_.GetAccessToken(authorization_code);
}

//ParsedResponse AccessLink::GetExercises(const std::string &access_token) {
//    Request request_body{"/exercises", {{"access_token", access_token}}};
//    return oauth_.Get(request_body);
//}

//ParsedResponse AccessLink::GetSleep(const std::string &access_token) {
//    Request request_body{"/users/sleep/", {{"access_token", access_token}}};
//    return oauth_.Get(request_body);
//}
//
//ParsedResponse AccessLink::GetRecharge(const std::string &access_token) {
//    Request request_body = {"/users/nightly-recharge/", {{"access_token", access_token}}};
//    return oauth_.Get(request_body);
//}

ParsedResponse AccessLink::GetUserdata(const std::string &access_token, const std::string &user_id) {
    Request request_body{"/users/" + user_id, {{"access_token", access_token}}};
    oauth_.PrepareRequest(request_body);
    return oauth_.Get(request_body.CprUrl(), request_body.CprHeader());
}

ParsedResponse AccessLink::RegisterUser(const std::string &access_token) {
    return users_.Record(access_token);
}