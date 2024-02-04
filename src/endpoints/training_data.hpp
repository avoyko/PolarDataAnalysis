//#pragma once
//
//#include <numeric>
//#include "resource.hpp"
//#include "training_data_transaction.hpp"
//
//class TrainingData : public Resource {
//
//    TrainingDataTransaction create_transaction(const int user_id, const std::string& access_token) {
//        std::string user_exercise_transactions_path =
//            "/users/" + std::to_string(user_id) + "/exercise-transactions";
//        auto response = _post(user_exercise_transactions_path, access_token);
//
//        return TrainingDataTransaction(oauth_, response, user_id,
//                                       access_token);  /// this must be changed cu
//    }
//
//    ~TrainingData() = default;
//};
