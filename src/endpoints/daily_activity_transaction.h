//#pragma once
//
//#include "transaction.hpp"
//
//
//class DailyActivityTransaction : public Transaction {
//
//    int list_activities() {
//        return this->_get(transaction_url_, access_token_);
//    }
//
//    int get_activity_summary(const std::string &url) {
//
//        return this->_get(url, access_token_);
//    }
//    int get_step_samples(const std::string &url) {
//
//        return this->_get(url + "/step-samples", access_token_);
//    }
//
//    int get_zone_samples(const std::string &url) {
//
//        return this->_get(url + "/zone-samples", access_token_);
//    }
//};