#pragma once
#include "oauth2.hpp"
#include "endpoints/users.hpp"
#include "endpoints/pull_notifications.hpp"
#include "endpoints/training_data.hpp"
#include "endpoints/physical_info.hpp"
#include "endpoints/daily_activity.hpp"

namespace Links {
const std::string AUTHORIZATION_URL = "https://flow.polar.com/oauth2/authorization";
const std::string ACCESS_TOKEN_URL = "https://polarremote.com/v2/oauth2/token";
const std::string ACCESSLINK_URL = "https://www.polaraccesslink.com/v3";
};  // namespace Links

class AccessLink {
public:
    AccessLink(const std::string &client_id, const std::string &client_secret,
               const std::string redirect_url = "")
        : oauth_(Links::ACCESSLINK_URL, Links::AUTHORIZATION_URL, Links::ACCESS_TOKEN_URL,
                 redirect_url, client_id, client_secret),
          phys_info_(oauth_),
          pull_notifications_(oauth_),
          daily_activity_(oauth_),
          users_(oauth_){};

    std::string get_auth_url();

    std::string get_access_token(const std::string &authorization_code);

    ParsedResponse get_exercises(const std::string &access_token);

    ParsedResponse get_sleep(const std::string &access_token);

    ParsedResponse get_recharge(const std::string &access_token);

    ParsedResponse get_userdata(const std::string &access_token, const std::string &user_id);

private:
    OAuth2Client oauth_;
    PhysicalInfo phys_info_;
    PullNotifications pull_notifications_;
    DailyActivity daily_activity_;
    Users users_;
};