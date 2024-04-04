#include "request.h"

std::string &Request::GetEndpoint() {
    return endpoint_;
}

cpr::Parameters &Request::CprParameters() {
    return parameters_;
}

cpr::Header &Request::CprHeader() {
    return headers_;
}

cpr::Url Request::CprUrl() {
    return {url_};
}

void Request::UpdateHeaders(const Headers &other) {
    for (const auto &each : other) {
        if (headers_.contains(each.first)) {
            headers_[each.first] = each.second;
        } else {
            headers_.insert(each);
        }
    }
}

void Request::UpdateUrl(const std::string &other_url) {
    url_ = other_url;
}
