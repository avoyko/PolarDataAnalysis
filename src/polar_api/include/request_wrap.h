#pragma once

#include <utility>
#include "cpr/cpr.h"

class RequestWrapper {
public:
    RequestWrapper() = default;

    RequestWrapper(std::string endpoint, cpr::Parameters query_args = {},
            cpr::Header headers = {}, std::string url = "")
        : endpoint_(std::move(endpoint)), parameters_(std::move(query_args)), headers_(std::move(headers)), url_(std::move(url)){};


    std::string &GetEndpoint();

    cpr::Parameters &CprParameters();

    cpr::Header &CprHeader();

    cpr::Url CprUrl();

    void UpdateHeaders(const cpr::Header &other);

    void UpdateUrl(const std::string &other_url);

private:
    std::string endpoint_;
    cpr::Parameters parameters_;
    cpr::Header headers_;
    std::string url_;
};