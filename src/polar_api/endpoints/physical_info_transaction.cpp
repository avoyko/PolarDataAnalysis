#include "physical_info_transaction.h"

ParsedResponse PhysicalInfoTransaction::ListPhysicalInfos() {
    Request request_body{"",
                         {{"url", transaction_url_}}};
    oauth_.PrepareRequest(request_body, access_token_);
    return GetData(request_body.CprUrl(), request_body.CprHeader());
}

ParsedResponse PhysicalInfoTransaction::GetPhysicalInfo(const std::string &url) {
    Request request_body{url};
    oauth_.PrepareRequest(request_body, access_token_);
    return GetData(request_body.CprUrl(), request_body.CprHeader());
}