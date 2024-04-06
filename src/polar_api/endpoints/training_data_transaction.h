#pragma once

#include "transaction.h"


class TrainingDataTransaction : public Transaction {
public:
    TrainingDataTransaction(const OAuth2Client &oauth, std::string transactionUrl,
                            std::string userId, std::string accessToken)
        : Transaction(oauth, std::move(transactionUrl), std::move(userId), std::move(accessToken)) {
    }

    ParsedResponse ListExercises();

    ParsedResponse GetExerciseSummary(const std::string &url);

    ParsedResponse GetGpx(const std::string &url);

    ParsedResponse GetTcx(const std::string &url);

    ParsedResponse GetHeartRateZones(const std::string &url);

    ParsedResponse GetAvailableSamples(const std::string &url);

    ParsedResponse GetSamples(const std::string &url);
};