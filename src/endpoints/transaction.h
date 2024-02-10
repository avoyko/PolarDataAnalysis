#pragma once

#include <utility>

#include "resource.h"


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
                             {{"url", transaction_url_},
                             }};

        oauth_.PrepareRequest(request_body, access_token_);
        return PutData(request_body);  ///what?
    }

protected:
    std::string transaction_url_;
    const int user_id_;
    std::string access_token_;
};