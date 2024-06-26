#pragma once

#include "training_data_transaction.h"

class TrainingData : public Resource {
public:
    explicit TrainingData(OAuth2Client &oauth) : Resource(oauth) {};

    TrainingDataTransaction CreateTransaction(const std::string &access_token,
                                              const std::string &user_id);

    ~TrainingData() = default;
};
