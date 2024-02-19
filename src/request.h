#pragma once

#include "utilities.h"

class Request {
public:
    Request() = default;

    Request(std::string_view endpoint, const Parameters &query_args = {},
            const Headers &headers = {}, const Body &body = "")
        : endpoint_(endpoint), parameters_(query_args), headers_(headers){};

    ~Request() = default;

    std::string &GetEndpoint();

    cpr::Parameters &CprParameters();

    cpr::Header &CprHeader();

    cpr::Url CprUrl();

    void UpdateHeaders(const Headers &other);

    void UpdateUrl(const std::string &other_url);

private:
    std::string endpoint_;
    Parameters parameters_;
    Headers headers_;
    std::string url_;
};