#include "training_data_transaction.h"

ParsedResponse TrainingDataTransaction::ListExercises() {
    Request request_body{Utils::EMPTY_ENDPOINT, {{"url", transaction_url_}}};
    oauth_.PrepareRequest(request_body, access_token_);
    return GetData(request_body.CprUrl(), request_body.CprHeader());
}
/// TODO: i still dont know what type of url we get (full/partial maybe?)
ParsedResponse TrainingDataTransaction::GetExerciseSummary(const std::string &url) {
    Request request_body{url};
    oauth_.PrepareRequest(request_body, access_token_);
    return GetData(request_body.CprUrl(), request_body.CprHeader());
}

ParsedResponse TrainingDataTransaction::GetGpx(const std::string &url) {
    Request request_body{url + "/heart-rate-zones", {}, Headers{{"Accept", "application/gpx+xml"}}};
    oauth_.PrepareRequest(request_body, access_token_);
    return GetData(request_body.CprUrl(), request_body.CprHeader());
}

ParsedResponse TrainingDataTransaction::GetTcx(const std::string &url) {
    Request request_body{url + "/tcx", {}, Headers{{"Accept", "application/vnd.garmin.tcx+xml"}}};
    oauth_.PrepareRequest(request_body, access_token_);
    return GetData(request_body.CprUrl(), request_body.CprHeader());
}

ParsedResponse TrainingDataTransaction::GetHeartRateZones(const std::string &url) {
    Request request_body{url + "/heart-rate-zones"};
    oauth_.PrepareRequest(request_body, access_token_);
    return GetData(request_body.CprUrl(), request_body.CprHeader());
}

ParsedResponse TrainingDataTransaction::GetAvailableSamples(const std::string &url) {
    Request request_body{url + "/samples"};
    oauth_.PrepareRequest(request_body, access_token_);
    return GetData(request_body.CprUrl(), request_body.CprHeader());
}

ParsedResponse TrainingDataTransaction::GetSamples(const std::string &url) {
    Request request_body{url};
    oauth_.PrepareRequest(request_body, access_token_);
    return GetData(request_body.CprUrl(), request_body.CprHeader());
}