#include "transaction.h"

ParsedResponse Transaction::Commit() {
    Request request_body{transaction_url_};
    oauth_.PrepareRequest(request_body, access_token_);
    return PutData(request_body.CprUrl(), request_body.CprHeader());  /// what?
}