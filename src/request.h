#pragma once

#include "utilities.hpp"

class Request {
public:
    Request() = default;
    Request(std::string_view endpoint, QueryArgs& query_args, Headers& headers)
        : endpoint_(endpoint), parameters_(query_args), headers_(headers){};

    ~Request() = default;

    void AddHeader(const std::string& header, const std::string& value) {
        headers_[header] = value;
    }

    std::string& GetHeaderValue(const std::string& header) {
        return headers_[header];
    }

private:
    std::string endpoint_;
    QueryArgs parameters_;
    Headers headers_;
};