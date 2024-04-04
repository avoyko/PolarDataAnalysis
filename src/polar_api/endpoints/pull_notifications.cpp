#include "pull_notifications.h"


ParsedResponse PullNotifications::List() {
    Request request_body{"/notifications"};
    oauth_.PrepareRequest(request_body);
    return GetData(request_body.CprUrl(), request_body.CprHeader());
}