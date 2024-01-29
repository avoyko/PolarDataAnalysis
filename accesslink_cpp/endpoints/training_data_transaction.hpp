#pragma once

#include "transaction.hpp"


class TrainingDataTransaction : public Transaction {
public:
    int list_exercises() {
        return _get(transaction_url_, access_token_);
    }

    int get_exercise_summary(const std::string& url) {
        return _get(url, access_token_);
    }

    int get_gpx(const std::string& url) {
        return _get(url + "/gpx", access_token_, Headers{{"Accept", "application/gpx+xml"}});
    }

    int get_tcx(const std::string& url) {
        return _get(url + "/tcx", access_token_,
                    Headers{{"Accept", "application/vnd.garmin.tcx+xml"}});
    }

    int get_heart_rate_zones(const std::string& url) {
        return _get(url + "/heart-rate-zones", access_token_);
    }

    int get_available_samples(const std::string& url) {
        return _get(url + "/samples", access_token_);
    }

    int get_samples(const std::string& url) {
        return _get(url, access_token_);
    }
};