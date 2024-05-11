#include "../include/accesslink.h"

std::string AccessLink::GetAuthUrl() {
    return oauth_.GetAuthorizationUrl();
}

ReadJson AccessLink::GetAccessToken(const std::string &authorization_code) {
    return oauth_.GetAccessToken(authorization_code);
}

WriteJson AccessLink::GetActivity(const std::string &access_token, const std::string &user_id) {
    DailyActivityTransaction transaction = daily_activity_.CreateTransaction(access_token, user_id);
    if (!transaction.IsValid()) {
        return {};
    }
    ReadJson activity_urls = transaction.ListActivities();
    std::vector<WriteJson> activity;
    for (const auto &each : activity_urls["activity-log"]) {
       // std::cout<<each<<std::endl;
        activity.emplace_back(transaction.GetActivity_summary(each.s()));
    }
    transaction.Commit();
    return activity;
}

WriteJson AccessLink::GetExercises(const std::string &access_token, const std::string &user_id) {
    TrainingDataTransaction transaction = training_data_.CreateTransaction(access_token, user_id);
    if (!transaction.IsValid()) {
        return {};
    }
    std::vector<WriteJson> exercises;
    ReadJson exercise_urls = transaction.ListExercises();
    for (const auto &each : exercise_urls["exercises"]) {
        exercises.emplace_back((transaction.GetExerciseSummary(each.s())));
    }
    transaction.Commit();
    return exercises;
}

WriteJson AccessLink::GetPhysicalInfo(const std::string &access_token, const std::string &user_id) {
    PhysicalInfoTransaction transaction = phys_info_.CreateTransaction(access_token, user_id);
    if (!transaction.IsValid()) {
        return {};
    }
    ReadJson physical_urls = transaction.ListPhysicalInfos();
    std::vector<WriteJson> physique;
    auto r = physical_urls["physical-informations"];
    for (const auto each : physical_urls["physical-informations"]) {
        physique.emplace_back(transaction.GetPhysicalInfo(each.s()));
    }
    transaction.Commit();
    return physique;
}

WriteJson AccessLink::GetSleep(const std::string &access_token, const std::string &user_id) {
    RequestWrapper request_body{"/users/sleep"};
    oauth_.PrepareRequest(request_body, access_token);
    ReadJson sleep_json = oauth_.Get(request_body.CprUrl(), request_body.CprHeader());
    std::vector<WriteJson> sleep;
    if (sleep_json.error()) {
        return {};
    }
    for (const auto &each : sleep_json) {
        sleep.emplace_back(each);
    }
    return sleep;
}

WriteJson AccessLink::GetRecharge(const std::string &access_token, const std::string &user_id) {
    RequestWrapper request_body = {"/users/nightly-recharge"};
    oauth_.PrepareRequest(request_body, access_token);
    return oauth_.Get(request_body.CprUrl(), request_body.CprParameters(),
                      request_body.CprHeader());
}

WriteJson AccessLink::GetUserdata(const std::string &access_token, const std::string &user_id) {
    RequestWrapper request_body{"/users/" + user_id, {}};
    oauth_.PrepareRequest(request_body, access_token);
    return oauth_.Get(request_body.CprUrl(), request_body.CprHeader());
}

ReadJson AccessLink::RegisterUser(const std::string &access_token) {
    return users_.Record(access_token);
}
