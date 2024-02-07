#pragma once

#include <utility>

#include "resource.hpp"


class Transaction : public Resource {
public:
    Transaction(const OAuth2Client &oauth, std::string transaction_url, const int user_id,
                std::string access_token)
            : Resource(oauth),
              transaction_url_(std::move(transaction_url)),
              user_id_(user_id),
              access_token_(std::move(access_token)) {};

    ParsedResponse Commit() {
        Request request_body{Utils::EMPTY_ENDPOINT,
                             QueryArgs{{"url",          transaction_url_},
                                       {"access_token", access_token_}}};
        return _put(request_body);
    }

protected:
    std::string transaction_url_;
    const int user_id_;
    std::string access_token_;
};