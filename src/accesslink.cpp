#include "accesslink.hpp"

std::string AccessLink::get_auth_url() {
    return oauth_.get_authorization_url();
}

json AccessLink::get_access_token(const std::string &authorization_code) {
    return oauth_.get_access_token(authorization_code);
}

ParsedResponse AccessLink::get_exercises(const std::string &access_token) {
    Request request_body{"/exercises", {{"access_token", access_token}}};
    return oauth_.get(request_body);
}

ParsedResponse AccessLink::get_sleep(const std::string &access_token) {
    Request request_body{"/users/sleep/", {{"access_token", access_token}}};
    return oauth_.get(request_body);
}

ParsedResponse AccessLink::get_recharge(const std::string &access_token) {
    Request request_body = {"/users/nightly-recharge/", {{"access_token", access_token}}};
    return oauth_.get(request_body);
}

ParsedResponse AccessLink::get_userdata(const std::string &access_token,
                                        const std::string &user_id) {
    Request request_body{"/users/" + user_id, {{"access_token", access_token}}};
    return oauth_.get(request_body);
}

ParsedResponse AccessLink::register_user(const std::string &access_token) {
    return users_.record(access_token);
}