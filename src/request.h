#pragma once

#include "utilities.hpp"

class Request {
public:
    Request() = default;

    Request(std::string_view endpoint, const QueryArgs &query_args, const Headers &headers, const Body &body = {},
            const std::string &auto_code = "")
            : endpoint_(endpoint), parameters_(query_args), headers_(headers), body_(body), auto_code_(auto_code) {};

    Request(std::string_view endpoint, const QueryArgs &query_args)
            : endpoint_(endpoint), parameters_(query_args), headers_(std::nullopt) {};

    ~Request() = default;

    void AddHeader(const std::string &header, const std::string &value) {
        headers_.value()[header] = value;
    }

//    std::string &GetHeaderValue(const std::string &header) {
//        //return headers_[header];
//    }

    const QueryArgs &GetParameters() const {   ///need to check if it is not empty i guess
        return parameters_.value();
    }

    const std::string &GetEndpoint() const {
        return endpoint_;
    }

    cpr::Parameters CprParameters() const {   ///need to check if it is not empty i guess
        return parameters_.value().ConvertToCpr();
    }

    cpr::Body CprBody() const {
        return body_.value();
    }

    cpr::Header CprHeader() const {
        return headers_.value();
    }


    cpr::Url CprUrl() const {
        std::string url = parameters_.value()["url"];
        return {url};
    }

    bool EmptyEndpoint() {
        return endpoint_.empty();
    }


private:
    std::string endpoint_;
    std::optional<QueryArgs> parameters_;
    std::optional<Headers> headers_;
    std::optional<Body> body_;
public:
    std::string auto_code_;
};