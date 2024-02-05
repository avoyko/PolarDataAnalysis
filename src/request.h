#pragma once

#include "utilities.hpp"

class Request {
public:
    Request() = default;

    Request(std::string_view endpoint, const QueryArgs &query_args, const Headers &headers)
            : endpoint_(endpoint), parameters_(query_args), headers_(headers) {};

    Request(std::string_view endpoint, const QueryArgs &query_args)
            : endpoint_(endpoint), parameters_(query_args), headers_(std::nullopt) {};

    ~Request() = default;

    void AddHeader(const std::string &header, const std::string &value) {
        // headers_[header] = value;
    }

    std::string &GetHeaderValue(const std::string &header) {
        //return headers_[header];
    }

    const QueryArgs &GetParameters() const {   ///need to check if it is not empty i guess
        return parameters_.value();
    }

    const std::string &GetEndpoint() const {
        return endpoint_;
    }


    bool EmptyEndpoint() {
        return endpoint_.empty();
    }

private:
    std::string endpoint_;
    std::optional<QueryArgs> parameters_;
    std::optional<Headers> headers_;
    std::optional<Body> body_;

};