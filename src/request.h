#pragma once

#include "utilities.hpp"

class Request {
public:
    Request() = default;

    Request(std::string_view endpoint, const QueryArgs &query_args, const Headers &headers,
            const std::string &auto_code = "")
            : endpoint_(endpoint), parameters_(query_args), headers_(headers), auto_code_(auto_code) {};

    Request(std::string_view endpoint, const QueryArgs &query_args)
            : endpoint_(endpoint), parameters_(query_args), headers_({}) {};

    ~Request() = default;

    void AddHeader(const std::string &header, const std::string &value) {
        headers_[header] = value;
    }

//    std::string &GetHeaderValue(const std::string &header) {
//        //return headers_[header];
//    }

    const QueryArgs &GetParameters() const {   ///need to check if it is not empty i guess
        return parameters_;
    }

    const std::string &GetEndpoint() const {
        return endpoint_;
    }

    cpr::Parameters CprParameters() const {   ///need to check if it is not empty i guess
        return parameters_.ConvertToCpr();
    }

    cpr::Header CprHeader() const {
        return headers_;
    }


    cpr::Url CprUrl() const {
        std::string url = parameters_["url"];
        return {url};
    }

    bool EmptyEndpoint() {
        return endpoint_.empty();
    }


private:
    std::string endpoint_;
    QueryArgs parameters_;
    Headers headers_;
public:
    std::string auto_code_;
};