#pragma once

#include "../oauth2.hpp"

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