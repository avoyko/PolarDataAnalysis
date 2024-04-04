#include "transaction.h"

class PhysicalInfoTransaction : public Transaction {
public:
    PhysicalInfoTransaction(const OAuth2Client &oauth, std::string transactionUrl, const int userId,
                            std::string accessToken)
            : Transaction(oauth, std::move(transactionUrl), userId, std::move(accessToken)) {};


    ParsedResponse ListPhysicalInfos();

    ParsedResponse GetPhysicalInfo(const std::string &url);

};