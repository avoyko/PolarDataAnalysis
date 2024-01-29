#pragma once

#include "resource.hpp"

class Transaction : public Resource {
public:
    Transaction(const OAuth2Client& oauth, const std::string& transaction_url, const int user_id,
                const std::string& access_token)
        : transaction_url_(transaction_url), user_id_(user_id), access_token_(access_token){};

    int Commit() {
        return _put(transaction_url_, access_token_);
    }

protected:
    const std::string transaction_url_;
    const int user_id_;
    const std::string access_token_;
};