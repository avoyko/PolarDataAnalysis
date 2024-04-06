#include "accesslink.h"

std::string AccessLink::GetAuthUrl() {
    return oauth_.GetAuthorizationUrl();
}

ParsedResponse AccessLink::GetAccessToken(const std::string &authorization_code) {
    return oauth_.GetAccessToken(authorization_code);
}

std::vector<ParsedResponse> AccessLink::GetActivity(const std::string &access_token,
                                                    const std::string &user_id) {
    DailyActivityTransaction transaction = daily_activity_.CreateTransaction(access_token, user_id);
    ParsedResponse all = transaction.ListActivities();
    std::vector<ParsedResponse> activity;
    for (const auto &each : all["activity-log"]) {
        activity.push_back(transaction.GetActivity_summary(each.s()));
    }
    transaction.Commit();
    return activity;
}

std::vector<ParsedResponse> AccessLink::GetExercises(const std::string &access_token,
                                                     const std::string &user_id) {

    TrainingDataTransaction transaction = training_data_.CreateTransaction(access_token, user_id);
    ParsedResponse all = transaction.ListExercises();
    std::vector<ParsedResponse> exercises;
    for (const auto &each : all["exercises"]) {
        exercises.push_back(transaction.GetExerciseSummary(each.s()));
    }
    transaction.Commit();
    return exercises;
}

std::vector<ParsedResponse> AccessLink::GetPhysicalInfo(const std::string &access_token,
                                                        const std::string &user_id) {
    PhysicalInfoTransaction transaction = phys_info_.CreateTransaction(access_token, user_id);
    ParsedResponse all = transaction.ListPhysicalInfos();
    std::vector<ParsedResponse> physique;
    for (const auto &each : all["activity-log"]) {
        physique.push_back(transaction.GetPhysicalInfo(each.s()));
    }
    transaction.Commit();
    return physique;
}

std::vector<ParsedResponse> AccessLink::GetSleep(const std::string &access_token,
                                                 const std::string &user_id) {
    RequestWrapper request_body{"/users/sleep/"};
    oauth_.PrepareRequest(request_body, access_token);
    ParsedResponse sleep_json = oauth_.Get(request_body.CprUrl(), request_body.CprParameters(),
                                           request_body.CprParameters());
    std::vector<ParsedResponse> sleep;
    for (const auto &each : sleep_json) {
        sleep.push_back(each);
    }
    return sleep;
}

ParsedResponse AccessLink::GetRecharge(const std::string &access_token,
                                       const std::string &user_id) {
    RequestWrapper request_body = {"/users/nightly-recharge/"};
    oauth_.PrepareRequest(request_body, access_token);
    return oauth_.Get(request_body.CprUrl(), request_body.CprParameters(),
                      request_body.CprHeader());
}

ParsedResponse AccessLink::GetUserdata(const std::string &access_token,
                                       const std::string &user_id) {
    RequestWrapper request_body{"/users/" + user_id, {}};
    oauth_.PrepareRequest(request_body, access_token);
    return oauth_.Get(request_body.CprUrl(), request_body.CprHeader());
}

ParsedResponse AccessLink::RegisterUser(const std::string &access_token) {
    return users_.Record(access_token);
}
