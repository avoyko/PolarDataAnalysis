#include "physical_info.h"


PhysicalInfoTransaction PhysicalInfo::CreateTransaction(const int user_id, const std::string &access_token) {
    std::string user_exercise_transactions_path = "/users/" + std::to_string(user_id) + "/exercise-transactions";
    RequestWrapper request_body{user_exercise_transactions_path};
    oauth_.PrepareRequest(request_body, access_token);
    auto response = PostData(request_body.CprUrl(), request_body.CprHeader());
    return {oauth_, response["resource-uri"].s(), user_id,
            access_token};
}