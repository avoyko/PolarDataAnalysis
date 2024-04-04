#pragma once

#include "endpoints/users.h"
#include "endpoints/pull_notifications.h"
#include "endpoints/training_data.h"
#include "endpoints/physical_info.h"
#include "endpoints/daily_activity.h"

namespace Links {
const std::string AUTHORIZATION_URL = "https://flow.polar.com/oauth2/authorization";
const std::string ACCESS_TOKEN_URL = "https://polarremote.com/v2/oauth2/token";
const std::string ACCESSLINK_URL = "https://www.polaraccesslink.com/v3";
};  // namespace Links

/// i couldn't come up with a better place to put it
struct PolarUser {
    const wjson exercises_info;
    const wjson activity_info;
    const wjson physical_info;
    const wjson sleep_info;
};

class AccessLink {
public:
    AccessLink(std::string_view client_id, std::string_view client_secret,
               std::string_view redirect_url = "")
        : oauth_(Links::ACCESSLINK_URL, Links::AUTHORIZATION_URL, Links::ACCESS_TOKEN_URL,
                 redirect_url, client_id, client_secret),
          phys_info_(oauth_),
          pull_notifications_(oauth_),
          daily_activity_(oauth_),
          training_data_(oauth_),
          users_(oauth_){};

    std::string GetAuthUrl();

    ParsedResponse GetAccessToken(const std::string &authorization_code);

    ParsedResponse GetExercises(const std::string &access_token);

    ParsedResponse GetSleep(const std::string &access_token);

    ParsedResponse GetRecharge(const std::string &access_token);

    ParsedResponse GetUserdata(const std::string &access_token, const std::string &user_id);

    ParsedResponse RegisterUser(const std::string &access_token);

private:
    OAuth2Client oauth_;
    PhysicalInfo phys_info_;
    PullNotifications pull_notifications_;
    DailyActivity daily_activity_;
    TrainingData training_data_;
    Users users_;
};