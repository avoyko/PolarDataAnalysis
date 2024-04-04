#include "pull_notifications.h"


ParsedResponse PullNotifications::List() {
    RequestWrapper request_body{"/notifications"};
    oauth_.PrepareRequest(request_body);
    return GetData(request_body.CprUrl(), request_body.CprHeader());
}