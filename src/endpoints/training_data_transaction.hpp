#pragma once

#include "transaction.hpp"

#include <utility>

class TrainingDataTransaction : public Transaction {
public:
    TrainingDataTransaction(const OAuth2Client &oauth, std::string transactionUrl, const int userId,
                            std::string accessToken)
            : Transaction(oauth, std::move(transactionUrl), userId, std::move(accessToken)) {
    }

//    ParsedResponse list_exercises() {
//        Request request_body{Utils::EMPTY_ENDPOINT,
//                             QueryArgs{{"url",          transaction_url_},
//                                       {"access_token", access_token_}}};
//        return GetData(request_body);
//    }
//
//
//    ParsedResponse get_exercise_summary(const std::string &url) {
//        Request request_body{Utils::EMPTY_ENDPOINT,
//                             QueryArgs{{"url",          url},
//                                       {"access_token", access_token_}}};
//        return GetData(request_body);
//    }
//
//    ParsedResponse get_gpx(const std::string &url) {
//        Request request_body{Utils::EMPTY_ENDPOINT,
//                             QueryArgs{{"url",          url + "/heart-rate-zones"},
//                                       {"access_token", access_token_}},
//                             Headers{{"Accept", "application/gpx+xml"}}};
//        return GetData(request_body);
//    }
//
//    ParsedResponse get_tcx(const std::string &url) {
//        Request request_body{Utils::EMPTY_ENDPOINT,
//                             QueryArgs{{"url",          url + "/tcx"},
//                                       {"access_token", access_token_}},
//                             Headers{{"Accept", "application/vnd.garmin.tcx+xml"}}};
//        return GetData(request_body);
//    }
//
//    ParsedResponse get_heart_rate_zones(const std::string &url) {
//        Request request_body{Utils::EMPTY_ENDPOINT,
//                             QueryArgs{{"url",          url + "/heart-rate-zones"},
//                                       {"access_token", access_token_}}};
//        return GetData(request_body);
//
//    }
//
//    ParsedResponse get_available_samples(const std::string &url) {
//        Request request_body{Utils::EMPTY_ENDPOINT,
//                             QueryArgs{{"url",          url + "/samples"},
//                                       {"access_token", access_token_}}};
//        return GetData(request_body);
//    }
//
//    ParsedResponse get_samples(const std::string &url) {
//        Request request_body{Utils::EMPTY_ENDPOINT,
//                             QueryArgs{{"url",          url},
//                                       {"access_token", access_token_}}};
//        return GetData(request_body);
//    }
};