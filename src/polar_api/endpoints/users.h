#pragma once  // streaming operators etc.

#include "resource.h"

class Users : public Resource {
public:
    explicit Users(OAuth2Client &oauth) : Resource(oauth){};

    ParsedResponse Record(const std::string &access_token,
                          boost::uuids::uuid member_id = boost::uuids::random_generator()());

    ParsedResponse Remove(const int user_id, std::string &access_token);

    ParsedResponse GetInformation(const int user_id, std::string &access_token);
};