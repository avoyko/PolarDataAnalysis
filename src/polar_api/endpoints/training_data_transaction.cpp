#include "training_data_transaction.h"

ReadJson TrainingDataTransaction::ListExercises() {
    RequestWrapper request_body{transaction_url_};
    oauth_.PrepareRequest(request_body, access_token_);
    return GetData(request_body.CprUrl(), request_body.CprHeader());
}

ReadJson TrainingDataTransaction::GetExerciseSummary(const std::string &url) {
    RequestWrapper request_body{url};
    oauth_.PrepareRequest(request_body, access_token_);
    return GetData(request_body.CprUrl(), request_body.CprHeader());
}

ReadJson TrainingDataTransaction::GetGpx(const std::string &url) {
    RequestWrapper request_body{url + "/heart-rate-zones", {}, cpr::Header{{"Accept", "application/gpx+xml"}}};
    oauth_.PrepareRequest(request_body, access_token_);
    return GetData(request_body.CprUrl(), request_body.CprHeader());
}

ReadJson TrainingDataTransaction::GetTcx(const std::string &url) {
    RequestWrapper request_body{url + "/tcx", {}, cpr::Header{{"Accept", "application/vnd.garmin.tcx+xml"}}};
    oauth_.PrepareRequest(request_body, access_token_);
    return GetData(request_body.CprUrl(), request_body.CprHeader());
}

ReadJson TrainingDataTransaction::GetHeartRateZones(const std::string &url) {
    RequestWrapper request_body{url + "/heart-rate-zones"};
    oauth_.PrepareRequest(request_body, access_token_);
    return GetData(request_body.CprUrl(), request_body.CprHeader());
}

ReadJson TrainingDataTransaction::GetAvailableSamples(const std::string &url) {
    RequestWrapper request_body{url + "/samples"};
    oauth_.PrepareRequest(request_body, access_token_);
    return GetData(request_body.CprUrl(), request_body.CprHeader());
}

ReadJson TrainingDataTransaction::GetSamples(const std::string &url) {
    RequestWrapper request_body{url};
    oauth_.PrepareRequest(request_body, access_token_);
    return GetData(request_body.CprUrl(), request_body.CprHeader());
}