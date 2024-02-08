#pragma once  // streaming operators etc.

#include "resource.hpp"

class Users : public Resource {
public:
    Users(OAuth2Client &oauth) : Resource(oauth) {};

    ParsedResponse Record(const std::string &access_token,
                          boost::uuids::uuid member_id = boost::uuids::random_generator()()) {
        Request request_body{"/users", {{"access_token", access_token}}};
        oauth_.PrepareRequest(request_body); // Now we prepare it here before Posting
        json my_json;
        my_json["member-id"] = boost::uuids::to_string(member_id);
        ParsedResponse reg_info = PostData(Body{my_json.dump()}, request_body.CprUrl(), request_body.CprHeader());
        return reg_info;
    }

//    ParsedResponse Remove(const int &user_id, std::string &access_token) {
//        Request request_body{"/users/" + std::to_string(user_id), {{"access_token", access_token}}};
//        return DeleteData(request_body);
//    }
//
//
//    ParsedResponse GetInformation(const int &user_id, std::string &access_token) {
//        Request request_body{"/users/" + std::to_string(user_id), {{"access_token", access_token}}};
//        return GetData(request_body);
//    }
};