#pragma once

#include <numeric>
#include "resource.hpp"
#include "training_data_transaction.hpp"

class TrainingData : public Resource {
    TrainingData() = default;

    TrainingDataTransaction create_transaction(const int& user_id,
                                               const std::string& access_token) {
        auto response =
            _post("/users/" + std::to_string(user_id) + "/exercise-transactions", access_token);

        return TrainingDataTransaction(oauth_, response, user_id, access_token); ///this must be changed cu
    }

    ~TrainingData() = default;
};
