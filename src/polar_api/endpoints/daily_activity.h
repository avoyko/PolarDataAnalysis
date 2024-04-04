#pragma once

#include "daily_activity_transaction.h"

class DailyActivity : public Resource {
public:
    explicit DailyActivity(OAuth2Client &oauth) : Resource(oauth) {};

    DailyActivityTransaction CreateTransaction(const int user_id, const std::string &access_token);
};