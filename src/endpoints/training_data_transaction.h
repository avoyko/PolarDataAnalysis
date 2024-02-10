#pragma once

#include "transaction.h"

#include <utility>

class TrainingDataTransaction : public Transaction {
public:
    TrainingDataTransaction(const OAuth2Client &oauth, std::string transactionUrl, const int userId,
                            std::string accessToken)
            : Transaction(oauth, std::move(transactionUrl), userId, std::move(accessToken)) {
    }

    ParsedResponse ListExercises() {
        Request request_body{Utils::EMPTY_ENDPOINT,
                             {{"url", transaction_url_}}};
        oauth_.PrepareRequest(request_body, access_token_);
        return GetData(request_body.CprUrl(), request_body.CprHeader());
    }
    ///TODO: i still dont know what type of url we get (full/partial maybe?)
    ParsedResponse GetExerciseSummary(const std::string &url) {
        Request request_body{url};
        oauth_.PrepareRequest(request_body, access_token_);
        return GetData(request_body.CprUrl(), request_body.CprHeader());
    }

    ParsedResponse GetGpx(const std::string &url) {
        Request request_body{url + "/heart-rate-zones", {},
                             Headers{{"Accept", "application/gpx+xml"}}};
        oauth_.PrepareRequest(request_body, access_token_);
        return GetData(request_body.CprUrl(), request_body.CprHeader());
    }

    ParsedResponse GetTcx(const std::string &url) {
        Request request_body{url + "/tcx", {},
                             Headers{{"Accept", "application/vnd.garmin.tcx+xml"}}};
        oauth_.PrepareRequest(request_body, access_token_);
        return GetData(request_body.CprUrl(), request_body.CprHeader());
    }

    ParsedResponse GetHeartRateZones(const std::string &url) {
        Request request_body{url + "/heart-rate-zones"};
        oauth_.PrepareRequest(request_body, access_token_);
        return GetData(request_body.CprUrl(), request_body.CprHeader());

    }

    ParsedResponse GetAvailableSamples(const std::string &url) {
        Request request_body{ url + "/samples"};
        oauth_.PrepareRequest(request_body, access_token_);
        return GetData(request_body.CprUrl(), request_body.CprHeader());
    }

    ParsedResponse GetSamples(const std::string &url) {
        Request request_body{url};
        oauth_.PrepareRequest(request_body, access_token_);
        return GetData(request_body.CprUrl(), request_body.CprHeader());
    }
};