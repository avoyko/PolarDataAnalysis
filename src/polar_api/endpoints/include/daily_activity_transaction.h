#pragma once

#include "transaction.h"

class DailyActivityTransaction : public Transaction {
public:
    DailyActivityTransaction(const OAuth2Client &oauth, std::string transactionUrl,
                             std::string userId, std::string accessToken)
        : Transaction(oauth, std::move(transactionUrl), std::move(userId),
                      std::move(accessToken)){};

    ReadJson ListActivities();

    ReadJson GetActivity_summary(const std::string &url);

    ReadJson GetStepSamples(const std::string &url);

    ReadJson GetZoneSamples(const std::string &url);
};