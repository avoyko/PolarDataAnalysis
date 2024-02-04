#pragma once

#include "transaction.hpp"

#include <utility>


class TrainingDataTransaction : public Transaction {
public:
    TrainingDataTransaction(const OAuth2Client& oauth,
                            std::string transactionUrl, const int userId, std::string accessToken)
        : Transaction(oauth,std::move(transactionUrl),userId,std::move(accessToken)) {
    }
    std::optional<ParsedResponse> list_exercises() {
        return _get(Utils::EMPTY_ENDPOINT, QueryArgs{{"url", transaction_url_}, {"access_token", access_token_}});
    }

    std::optional<ParsedResponse> get_exercise_summary(const std::string& url) {
        return _get(Utils::EMPTY_ENDPOINT, QueryArgs{{"url", url}, {"access_token", access_token_}});
    }

    std::optional<ParsedResponse> get_gpx(const std::string& url) {
        return _get(url + "/gpx", access_token_, Headers{{"Accept", "application/gpx+xml"}});

        return _get(Utils::EMPTY_ENDPOINT, QueryArgs{{"url", url + "/heart-rate-zones"}, {"access_token", access_token_}});


    }

    std::optional<ParsedResponse> get_tcx(const std::string& url) {
        return _get(url + "/tcx", access_token_,
                    Headers{{"Accept", "application/vnd.garmin.tcx+xml"}});

        return _get(Utils::EMPTY_ENDPOINT, QueryArgs{{"url", url + "/tcx"}, {"access_token", access_token_}});

    }

    std::optional<ParsedResponse> get_heart_rate_zones(const std::string& url) {
        return _get(Utils::EMPTY_ENDPOINT, QueryArgs{{"url", url + "/heart-rate-zones"}, {"access_token", access_token_}});
    }

    std::optional<ParsedResponse> get_available_samples(const std::string& url) {
        return _get(Utils::EMPTY_ENDPOINT, QueryArgs{{"url", url + "/samples"}, {"access_token", access_token_}});
    }

    std::optional<ParsedResponse> get_samples(const std::string& url) {
        return _get(Utils::EMPTY_ENDPOINT, QueryArgs{{"url", url}, {"access_token", access_token_}});
    }
};