#include "pull_notifications.h"

ReadJson PullNotifications::List() {
    RequestWrapper request_body{"/notifications"};
    oauth_.PrepareRequest(request_body);
    return GetData(request_body.CprUrl(), request_body.CprHeader());
}