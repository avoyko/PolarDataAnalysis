#pragma once  // streaming operators etc.

#include "resource.hpp"

class Users : public Resource {
public:
    Users(OAuth2Client &oauth) : Resource(oauth) {};

    ParsedResponse record(
            const std::string &access_token,
            boost::uuids::uuid member_id = boost::uuids::random_generator()()) {

        return _post({"/users", {{"access_token", access_token}},
                      Headers{{"member-id", boost::uuids::to_string(member_id)}}});
    }

    ParsedResponse remove(const int &user_id, std::string &access_token) {
        return _delete({"/users/" + std::to_string(user_id), {{"access_token", access_token}}});
    }


    ParsedResponse get_information(const int &user_id, std::string &access_token) {
        return _get({"/users/" + std::to_string(user_id), {{"access_token", access_token}}});
    }
};