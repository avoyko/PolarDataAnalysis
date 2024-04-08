#pragma once

#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "resource.h"


class Users : public Resource {
public:
    explicit Users(OAuth2Client &oauth) : Resource(oauth){};

    ReadJson Record(const std::string &access_token,
                          boost::uuids::uuid member_id = boost::uuids::random_generator()());

    ReadJson Remove(int user_id, std::string &access_token);

    ReadJson GetInformation(int user_id, std::string &access_token);
};