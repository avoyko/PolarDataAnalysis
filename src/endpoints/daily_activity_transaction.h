#pragma once

#include "transaction.h"

class DailyActivityTransaction : public Transaction {
public:
    DailyActivityTransaction(const OAuth2Client &oauth, std::string transactionUrl,
                             const int userId, std::string accessToken)
        : Transaction(oauth, std::move(transactionUrl), userId, std::move(accessToken)){};

    ParsedResponse ListActivities();

    ParsedResponse GetActivity_summary(const std::string &url);

    ParsedResponse GetStepSamples(const std::string &url);

    ParsedResponse GetZoneSamples(const std::string &url);
};