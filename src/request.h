#pragma once

#include "utilities.hpp"

class Request {
public:
    Request() = default;

    Request(std::string_view endpoint, const QueryArgs &query_args, const Headers &headers, std::string_view url = "")
            : endpoint_(endpoint), parameters_(query_args), headers_(headers), url_(url) {};

    Request(std::string_view endpoint, const QueryArgs &query_args)
            : endpoint_(endpoint), parameters_(query_args) {};

    ~Request() = default;

    void AddHeader(const std::string &header, const std::string &value) {
        headers_[header] = value;
    }

    QueryArgs &GetParameters() {   // TODO need to check if it is not empty i guess
        return parameters_;
    }

    std::string &GetEndpoint() {
        return endpoint_;
    }

    cpr::Parameters CprParameters() {   // TODO need to check if it is not empty i guess
        return parameters_.ConvertToCpr();
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

    bool ContainsParameter(const std::string &parameter) {
        return parameters_.Contains(parameter);
    }

    std::string GetParameter(const std::string &parameter) {
        return parameters_[parameter];
    }

    bool RemoveParameter(const std::string &parameter) {
        return parameters_.Erase(parameter);
    }

private:
    std::string endpoint_;
    QueryArgs parameters_;
    Headers headers_;
    std::string url_;
};