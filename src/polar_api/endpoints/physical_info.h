#pragma once

#include "physical_info_transaction.h"

class PhysicalInfo : public Resource {
public:
    explicit PhysicalInfo(OAuth2Client &oauth) : Resource(oauth){};

    PhysicalInfoTransaction CreateTransaction(const std::string &access_token,
                                              const std::string &user_id);
};