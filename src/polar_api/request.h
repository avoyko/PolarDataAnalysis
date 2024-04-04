#pragma once

#include <utility>

#include "utilities.h"

class Request {
public:
    Request() = default;

    Request(std::string_view endpoint, Parameters query_args = {},
            Headers headers = {}, const Body &body = "")
        : endpoint_(endpoint), parameters_(std::move(query_args)), headers_(std::move(headers)){};


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