#pragma once

#include "utilities.h"

class Request {
public:
    Request() = default;

    Request(std::string_view endpoint, const Parameters &query_args = {}, const Headers &headers = {},
            const Body &body = "")
            : endpoint_(endpoint), parameters_(query_args), headers_(headers) {};

    ~Request() = default;

    void AddHeader(const std::string &header, const std::string &value) {
        headers_[header] = value;
    }

    std::string &GetEndpoint() {
        return endpoint_;
    }

    cpr::Parameters CprParameters() {
        return parameters_;
    }

    cpr::Header &CprHeader() {
        return headers_;
    }

    cpr::Url CprUrl() const {
        return url_;
    }

    void UpdateHeaders(const Headers &other) {
        for (const auto &each: other) {
            if (headers_.contains(each.first)) {
                headers_[each.first] = each.second;
            } else {
                headers_.insert(each);
            }
        }
    }

    void UpdateUrl(const std::string &other_url) {
        url_ = other_url;
    }

private:
    std::string endpoint_;
    Parameters parameters_;
    Headers headers_;
    std::string url_;
};