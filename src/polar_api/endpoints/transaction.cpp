#include "transaction.h"

ReadJson Transaction::Commit() {
    RequestWrapper request_body{transaction_url_};
    oauth_.PrepareRequest(request_body, access_token_);
    return PutData(request_body.CprUrl(), request_body.CprHeader());  /// what?
}
bool Transaction::IsValid() {
    return !transaction_url_.empty();
}
