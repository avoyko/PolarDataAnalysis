#include "request_wrap.h"

std::string &RequestWrapper::GetEndpoint() {
    return endpoint_;
}

cpr::Parameters &RequestWrapper::CprParameters() {
    return parameters_;
}

cpr::Header &RequestWrapper::CprHeader() {
    return headers_;
}

cpr::Url RequestWrapper::CprUrl() {
    return {url_};
}

void RequestWrapper::UpdateHeaders(const cpr::Header &other) {
    for (const auto &each : other) {
        if (headers_.contains(each.first)) {
            headers_[each.first] = each.second;
        } else {
            headers_.insert(each);
        }
    }
}

void RequestWrapper::UpdateUrl(const std::string &other_url) {
    url_ = other_url;
}
