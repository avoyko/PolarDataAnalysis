#pragma once

#include "../oauth2.h"

class Resource {
public:
    explicit Resource(const OAuth2Client &oauth) : oauth_(oauth) {};

    template<typename ...CprRequestParameters>
    ParsedResponse GetData(CprRequestParameters &&... parameters) {
        return oauth_.Get(std::forward<CprRequestParameters>(parameters)...);
    }

    template<typename ...CprRequestParameters>
    ParsedResponse PostData(CprRequestParameters &&... parameters) {
        return oauth_.Post(std::forward<CprRequestParameters>(parameters)...);
    }

    template<typename ...CprRequestParameters>
    ParsedResponse PutData(CprRequestParameters &&... parameters) {
        return oauth_.Put(std::forward<CprRequestParameters>(parameters)...);
    }
    template<typename ...CprRequestParameters>
    ParsedResponse DeleteData(CprRequestParameters &&... parameters) {
        return oauth_.Delete(std::forward<CprRequestParameters>(parameters)...);
    }

    ~Resource() = default;

protected:
    OAuth2Client oauth_;
};