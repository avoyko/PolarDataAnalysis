#include "../include/training_data.h"

TrainingDataTransaction TrainingData::CreateTransaction(const std::string &access_token,
                                                        const std::string &user_id) {
    std::string user_exercise_transactions_path = "/users/" + user_id + "/exercise-transactions";
    RequestWrapper request_body{user_exercise_transactions_path};
    oauth_.PrepareRequest(request_body, access_token);
    ReadJson response = PostData(request_body.CprUrl(), request_body.CprHeader());
    std::string resource_uri;
    if (!response.error()) {
        resource_uri = response["resource-uri"].s();
    }
    return {oauth_, resource_uri, user_id, access_token};
}