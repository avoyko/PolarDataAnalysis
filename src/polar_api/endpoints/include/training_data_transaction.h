#pragma once

#include "transaction.h"

class TrainingDataTransaction : public Transaction {
public:
    TrainingDataTransaction(const OAuth2Client &oauth, std::string transactionUrl,
                             std::string userId, std::string accessToken)
        : Transaction(oauth, std::move(transactionUrl),
                      std::move(userId), std::move(accessToken)) {
    }

    ReadJson ListExercises();

    ReadJson GetExerciseSummary(const std::string &url);

    ReadJson GetGpx(const std::string &url);

    ReadJson GetTcx(const std::string &url);

    ReadJson GetHeartRateZones(const std::string &url);

    ReadJson GetAvailableSamples(const std::string &url);

    ReadJson GetSamples(const std::string &url);
};