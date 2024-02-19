#pragma once

#include "../oauth2.h"
#include "physical_info_transaction.h"

class PhysicalInfo : public Resource {
public:
    explicit PhysicalInfo(OAuth2Client &oauth) : Resource(oauth){};

    PhysicalInfoTransaction CreateTransaction(const int user_id, const std::string &access_token);
};