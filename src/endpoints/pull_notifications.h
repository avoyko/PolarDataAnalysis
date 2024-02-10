#pragma once

#include "../oauth2.h"

class PullNotifications : public Resource {
public:
    explicit PullNotifications(OAuth2Client &oauth) : Resource(oauth) {};

    ParsedResponse List() {
        Request request_body{"/notifications"};
        oauth_.PrepareRequest(request_body);
        return GetData(request_body.CprUrl(), request_body.CprHeader());
    }
};