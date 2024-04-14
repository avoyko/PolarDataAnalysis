#pragma once

#include "daily_activity_transaction.h"

class DailyActivity : public Resource {
public:
    explicit DailyActivity(OAuth2Client &oauth) : Resource(oauth){};

    DailyActivityTransaction CreateTransaction(const std::string &access_token,
                                               const std::string &user_id);
};