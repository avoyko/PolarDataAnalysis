#pragma once

#include "../oauth2.h"
#include "resource.h"

class PullNotifications : public Resource {
public:
    explicit PullNotifications(OAuth2Client &oauth) : Resource(oauth) {};

    ParsedResponse List();
};