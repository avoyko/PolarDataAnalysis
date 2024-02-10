#include "transaction.h"

class PhysicalInfoTransaction : public Transaction {
public:
    PhysicalInfoTransaction(const OAuth2Client &oauth, std::string transactionUrl, const int userId,
                            std::string accessToken)
            : Transaction(oauth, std::move(transactionUrl), userId, std::move(accessToken)) {};


    ParsedResponse ListPhysicalInfos() {
        Request request_body{Utils::EMPTY_ENDPOINT,
                             {{"url", transaction_url_}}};
        oauth_.PrepareRequest(request_body, access_token_);
        return GetData(request_body.CprUrl(), request_body.CprHeader());
    }

    ParsedResponse GetPhysicalInfo(const std::string &url) {
        Request request_body{url};
        oauth_.PrepareRequest(request_body, access_token_);
        return GetData(request_body.CprUrl(), request_body.CprHeader());
    }

};