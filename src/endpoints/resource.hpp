#pragma once

#include "../oauth2.hpp"

class Resource {
public:
    explicit Resource(const OAuth2Client &oauth) : oauth_(oauth) {};


//    ParsedResponse GetData(Request &request) {
//        return oauth_.Get(request);
//    }

    template<typename ...CprRequestParameters>
    ParsedResponse PostData(CprRequestParameters &&... parameters) {
        return oauth_.Post(std::forward<CprRequestParameters>(parameters)...);
    }

//    ParsedResponse PutData(Request &request) {
//        return oauth_.Put(request);
//    }
//
//    ParsedResponse DeleteData(Request &request) {
//        return oauth_.Delete(request);
//    }

    ~Resource() = default;

protected:
    OAuth2Client oauth_;
};