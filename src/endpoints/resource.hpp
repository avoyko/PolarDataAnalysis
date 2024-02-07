#pragma once

#include "../oauth2.hpp"

class Resource {
public:
    explicit Resource(const OAuth2Client &oauth) : oauth_(oauth){};


    ParsedResponse _get(Request &request) {
        return oauth_.get(request);
    }


    ParsedResponse _post(Request &request) {
        return oauth_.post(request);
    }


    ParsedResponse _put(Request &request) {
        return oauth_.put(request);
    }

    ParsedResponse _delete(Request &request) {
        return oauth_.remove(request);
    }

    ~Resource() = default;

protected:
    OAuth2Client oauth_;
};