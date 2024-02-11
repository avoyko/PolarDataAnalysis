#pragma once

#include "transaction.h"


class DailyActivityTransaction : public Transaction {
public:
    DailyActivityTransaction(const OAuth2Client &oauth, std::string transactionUrl, const int userId,
                             std::string accessToken)
            : Transaction(oauth, std::move(transactionUrl), userId, std::move(accessToken)) {};


    ParsedResponse ListActivities() {
        Request request_body{Utils::EMPTY_ENDPOINT,
                             {{"url", transaction_url_}}};
        oauth_.PrepareRequest(request_body, access_token_);
        return GetData(request_body.CprUrl(), request_body.CprHeader());
    }

    ParsedResponse GetActivity_summary(const std::string &url) {
        Request request_body{url};
        oauth_.PrepareRequest(request_body, access_token_);
        return GetData(request_body.CprUrl(), request_body.CprHeader());
    }

    ParsedResponse GetStepSamples(const std::string &url) {
        Request request_body{url + "/step-samples"};
        oauth_.PrepareRequest(request_body, access_token_);
        return GetData(request_body.CprUrl(), request_body.CprHeader());
    }

    ParsedResponse GetZoneSamples(const std::string &url) {
        Request request_body{url + "/zone-samples"};
        oauth_.PrepareRequest(request_body, access_token_);
        return GetData(request_body.CprUrl(), request_body.CprHeader());
    }
};