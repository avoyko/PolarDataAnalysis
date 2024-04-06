#pragma once

#include "resource.h"

class Transaction : public Resource {
public:
    Transaction(const OAuth2Client &oauth, std::string transaction_url, std::string user_id,
                std::string access_token)
        : Resource(oauth),
          transaction_url_(std::move(transaction_url)),
          user_id_(std::move(user_id)),
          access_token_(std::move(access_token)){};

    ParsedResponse Commit();

protected:
    const std::string transaction_url_;
    const std::string transaction_id_;
    const std::string user_id_;
    const std::string access_token_;
};