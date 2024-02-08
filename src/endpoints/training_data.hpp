#pragma once

#include <numeric>
#include "resource.hpp"
#include "training_data_transaction.hpp"

class TrainingData : public Resource {

//    TrainingDataTransaction create_transaction(const int user_id, const std::string &access_token) {
//        std::string user_exercise_transactions_path =
//                "/users/" + std::to_string(user_id) + "/exercise-transactions";
//        Request request_body{user_exercise_transactions_path, {{"access_token", access_token}}};
//        auto response = PostData(request_body);
//        ///damn, we might pass json or just string,  i dont know what to do :-(
//        return TrainingDataTransaction(oauth_, " response", user_id,
//                                       access_token);  /// this must be changed cu
//    }


    ~TrainingData() = default;
};
