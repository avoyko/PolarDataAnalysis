#include "training_data_transaction.h"

ParsedResponse TrainingDataTransaction::ListExercises() {
    RequestWrapper request_body{"", {{"url", transaction_url_}}};
    oauth_.PrepareRequest(request_body, access_token_);
    return GetData(request_body.CprUrl(), request_body.CprHeader());
}

ParsedResponse TrainingDataTransaction::GetExerciseSummary(const std::string &url) {
    RequestWrapper request_body{url};
    oauth_.PrepareRequest(request_body, access_token_);
    return GetData(request_body.CprUrl(), request_body.CprHeader());
}

ParsedResponse TrainingDataTransaction::GetGpx(const std::string &url) {
    RequestWrapper request_body{url + "/heart-rate-zones", {}, cpr::Header{{"Accept", "application/gpx+xml"}}};
    oauth_.PrepareRequest(request_body, access_token_);
    return GetData(request_body.CprUrl(), request_body.CprHeader());
}

ParsedResponse TrainingDataTransaction::GetTcx(const std::string &url) {
    RequestWrapper request_body{url + "/tcx", {}, cpr::Header{{"Accept", "application/vnd.garmin.tcx+xml"}}};
    oauth_.PrepareRequest(request_body, access_token_);
    return GetData(request_body.CprUrl(), request_body.CprHeader());
}

ParsedResponse TrainingDataTransaction::GetHeartRateZones(const std::string &url) {
    RequestWrapper request_body{url + "/heart-rate-zones"};
    oauth_.PrepareRequest(request_body, access_token_);
    return GetData(request_body.CprUrl(), request_body.CprHeader());
}

ParsedResponse TrainingDataTransaction::GetAvailableSamples(const std::string &url) {
    RequestWrapper request_body{url + "/samples"};
    oauth_.PrepareRequest(request_body, access_token_);
    return GetData(request_body.CprUrl(), request_body.CprHeader());
}

ParsedResponse TrainingDataTransaction::GetSamples(const std::string &url) {
    RequestWrapper request_body{url};
    oauth_.PrepareRequest(request_body, access_token_);
    return GetData(request_body.CprUrl(), request_body.CprHeader());
}