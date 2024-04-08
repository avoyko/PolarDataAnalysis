#include "physical_info_transaction.h"

ReadJson PhysicalInfoTransaction::ListPhysicalInfos() {
    RequestWrapper request_body{transaction_url_};
    oauth_.PrepareRequest(request_body, access_token_);
    return GetData(request_body.CprUrl(), request_body.CprHeader());
}

ReadJson PhysicalInfoTransaction::GetPhysicalInfo(const std::string &url) {
    RequestWrapper request_body{url};
    oauth_.PrepareRequest(request_body, access_token_);
    return GetData(request_body.CprUrl(), request_body.CprHeader());
}