#include "../include/daily_activity_transaction.h"

ReadJson DailyActivityTransaction::ListActivities() {
    RequestWrapper request_body{transaction_url_};
    oauth_.PrepareRequest(request_body, access_token_);
    return GetData(request_body.CprUrl(), request_body.CprHeader());
}

ReadJson DailyActivityTransaction::GetActivity_summary(const std::string &url) {
    RequestWrapper request_body{url};
    oauth_.PrepareRequest(request_body, access_token_);
    return GetData(request_body.CprUrl(), request_body.CprHeader());
}

ReadJson DailyActivityTransaction::GetStepSamples(const std::string &url) {
    RequestWrapper request_body{url + "/step-samples"};
    oauth_.PrepareRequest(request_body, access_token_);
    return GetData(request_body.CprUrl(), request_body.CprHeader());
}

ReadJson DailyActivityTransaction::GetZoneSamples(const std::string &url) {
    RequestWrapper request_body{url + "/zone-samples"};
    oauth_.PrepareRequest(request_body, access_token_);
    return GetData(request_body.CprUrl(), request_body.CprHeader());
}