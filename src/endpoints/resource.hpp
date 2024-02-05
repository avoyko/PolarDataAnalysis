#pragma once

#include "../oauth2.hpp"

class Resource {
public:
    explicit Resource(const OAuth2Client &oauth) : oauth_(oauth){};


    std::optional<ParsedResponse> _get(const Request &request) {
        return oauth_.get(request);
    }


    std::optional<ParsedResponse> _post(const Request &request) {
        return oauth_.post(request);
    }


    std::optional<ParsedResponse> _put(const Request &request) {
        return oauth_.put(request);
    }

    std::optional<ParsedResponse> _delete(const Request &request) {
        return oauth_.remove(request);
    }

    ~Resource() = default;

protected:
    OAuth2Client oauth_;
};