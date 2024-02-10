#pragma once

#include "transaction.h"

#include <utility>

class TrainingDataTransaction : public Transaction {
public:
    TrainingDataTransaction(const OAuth2Client &oauth, std::string transactionUrl, const int userId,
                            std::string accessToken)
            : Transaction(oauth, std::move(transactionUrl), userId, std::move(accessToken)) {
    }

    ParsedResponse list_exercises() {
        Request request_body{Utils::EMPTY_ENDPOINT,
                             {{"url", transaction_url_}}};
        oauth_.PrepareRequest(request_body, access_token_);
        return GetData(request_body.CprUrl(), request_body.CprHeader());
    }
    ///TODO: i still dont know what type of url we get (full/partial maybe?)
    ParsedResponse get_exercise_summary(const std::string &url) {
        Request request_body{Utils::EMPTY_ENDPOINT,
                             {{"url", url}}};
        oauth_.PrepareRequest(request_body, access_token_);
        return GetData(request_body.CprUrl(), request_body.CprHeader());
    }

    ParsedResponse get_gpx(const std::string &url) {
        Request request_body{url + "/heart-rate-zones", {},
                             Headers{{"Accept", "application/gpx+xml"}}};
        oauth_.PrepareRequest(request_body, access_token_);
        return GetData(request_body.CprUrl(), request_body.CprHeader());
    }

    ParsedResponse get_tcx(const std::string &url) {
        Request request_body{url + "/tcx", {},
                             Headers{{"Accept", "application/vnd.garmin.tcx+xml"}}};
        oauth_.PrepareRequest(request_body, access_token_);
        return GetData(request_body.CprUrl(), request_body.CprHeader());
    }

    ParsedResponse get_heart_rate_zones(const std::string &url) {
        Request request_body{url + "/heart-rate-zones"};
        oauth_.PrepareRequest(request_body, access_token_);
        return GetData(request_body.CprUrl(), request_body.CprHeader());

    }

    ParsedResponse get_available_samples(const std::string &url) {
        Request request_body{ url + "/samples"};
        oauth_.PrepareRequest(request_body, access_token_);
        return GetData(request_body.CprUrl(), request_body.CprHeader());
    }

    ParsedResponse get_samples(const std::string &url) {
        Request request_body{url};
        oauth_.PrepareRequest(request_body, access_token_);
        return GetData(request_body.CprUrl(), request_body.CprHeader());
    }
};