
#include "accesslink.hpp"

std::string AccessLink::get_auth_url() {
    return oauth_.get_authorization_url();
}

std::string AccessLink::get_access_token(const std::string &authorization_code) {
    return oauth_.get_access_token(authorization_code);
}

ParsedResponse AccessLink::get_exercises(const std::string &access_token) {
    return oauth_.get("/exercises", {{"access_token", access_token}});
}

ParsedResponse AccessLink::get_sleep(const std::string &access_token) {
    return oauth_.get("/users/sleep/", {{"access_token", access_token}});
}

ParsedResponse AccessLink::get_recharge(const std::string &access_token) {
    return oauth_.get("/users/nightly-recharge/", {{"access_token", access_token}});
}

ParsedResponse AccessLink::get_userdata(const std::string &access_token, const std::string &user_id) {
    return oauth_.get("/users/" + user_id, {{"access_token", access_token}});
}