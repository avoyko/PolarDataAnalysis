#pragma once

#include <numeric>
#include "resource.h"
#include "training_data_transaction.h"

class TrainingData : public Resource {
public:
    explicit TrainingData(OAuth2Client &oauth) : Resource(oauth) {};

    TrainingDataTransaction CreateTransaction(const int user_id, const std::string &access_token);

   ///there is smth wrong with ParsedResponse object (I cannot access string)


    ~TrainingData() = default;
};
