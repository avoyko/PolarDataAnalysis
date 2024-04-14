#pragma once

#include "../../include/oauth2.h"

class Resource {
public:
    explicit Resource(const OAuth2Client &oauth) : oauth_(oauth) {};

    template<typename ...CprRequestParameters>
    ReadJson GetData(CprRequestParameters &&... parameters) {
        return oauth_.Get(std::forward<CprRequestParameters>(parameters)...);
    }

    template<typename ...CprRequestParameters>
    ReadJson PostData(CprRequestParameters &&... parameters) {
        return oauth_.Post(std::forward<CprRequestParameters>(parameters)...);
    }

    template<typename ...CprRequestParameters>
    ReadJson PutData(CprRequestParameters &&... parameters) {
        return oauth_.Put(std::forward<CprRequestParameters>(parameters)...);
    }
    template<typename ...CprRequestParameters>
    ReadJson DeleteData(CprRequestParameters &&... parameters) {
        return oauth_.Delete(std::forward<CprRequestParameters>(parameters)...);
    }

    ~Resource() = default;

protected:
    OAuth2Client oauth_;
};