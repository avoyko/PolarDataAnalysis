#pragma once

#include <numeric>
#include "resource.h"
#include "training_data_transaction.h"

class TrainingData : public Resource {
public:
    explicit TrainingData(OAuth2Client &oauth) : Resource(oauth) {};

    TrainingDataTransaction CreateTransaction(const int user_id, const std::string &access_token) {
        std::string user_exercise_transactions_path = "/users/" + std::to_string(user_id) + "/exercise-transactions";
        Request request_body{user_exercise_transactions_path};
        oauth_.PrepareRequest(request_body, access_token);
        auto response = PostData(request_body.CprUrl(), request_body.CprHeader());
        return {oauth_, response["resource-uri"], user_id,
                access_token};
    }


    ~TrainingData() = default;
};
