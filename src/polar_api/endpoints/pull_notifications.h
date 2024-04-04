#pragma once

#include "resource.h"

class PullNotifications : public Resource {
public:
    explicit PullNotifications(OAuth2Client &oauth) : Resource(oauth) {};

    ParsedResponse List();
};