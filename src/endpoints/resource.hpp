#pragma once

#include "../oauth2.hpp"

class Resource {
public:
    explicit Resource(const OAuth2Client &oauth) : oauth_(oauth){};


    ParsedResponse GetData(Request &request) {
        return oauth_.Get(request);
    }


    ParsedResponse PostData(Request &request) {
        return oauth_.Post(request);
    }


    ParsedResponse PutData(Request &request) {
        return oauth_.Put(request);
    }

    ParsedResponse DeleteData(Request &request) {
        return oauth_.Delete(request);
    }

    ~Resource() = default;

protected:
    OAuth2Client oauth_;
};