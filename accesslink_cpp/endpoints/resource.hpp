#pragma once

#include <cpr/cpr.h>

#include <utility>

#include "../oauth2.hpp"
#include "string"
#include "unordered_map"
using Headers = std::unordered_map<std::string, std::string>;

class Resource {
public:
    Resource(const OAuth2Client &oauth) : oauth_(oauth){};

    template <typename... Args>
    int _get(Args &&...args) {
        return oauth_.get(std::forward<Args>(args)...);
    }

    template <typename... Args>
    int _post(Args &&...args) {
        return oauth_.post(std::forward<Args>(args)...);
    }

    template <typename... Args>
    int _put(Args &&...args) {
        return oauth_.put(std::forward<Args>(args)...);
    }

    template <typename... Args>
    int _delete(Args &&...args) {
        return oauth_.remove(std::forward<Args>(args)...);
    }

    ~Resource() = default;

protected:
    OAuth2Client oauth_;
};