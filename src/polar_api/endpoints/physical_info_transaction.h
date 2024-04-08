#pragma once

#include "transaction.h"

class PhysicalInfoTransaction : public Transaction {
public:
    PhysicalInfoTransaction(const OAuth2Client &oauth, std::string transactionUrl,
                            std::string userId, std::string accessToken)
        : Transaction(oauth, std::move(transactionUrl), std::move(userId),
                      std::move(accessToken)){};

    ReadJson ListPhysicalInfos();

    ReadJson GetPhysicalInfo(const std::string &url);
};