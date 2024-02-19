#include "users.h"

ParsedResponse Users::Record(const std::string &access_token, boost::uuids::uuid member_id) {
    wjson my_json;
    my_json["member-id"] = boost::uuids::to_string(member_id);
    Request request_body{"/users", {}};
    oauth_.PrepareRequest(request_body, access_token);
    ParsedResponse reg_info =
            PostData(Body{my_json.dump()}, request_body.CprUrl(), request_body.CprHeader());
    return reg_info;
}

ParsedResponse Users::Remove(const int user_id, std::string &access_token) {
    Request request_body{"/users/" + std::to_string(user_id)};
    oauth_.PrepareRequest(request_body, access_token);
    return DeleteData(request_body.CprUrl(), request_body.CprParameters(),
                      request_body.CprHeader());
}

ParsedResponse Users::GetInformation(const int user_id, std::string &access_token) {
    Request request_body{"/users/" + std::to_string(user_id)};
    oauth_.PrepareRequest(request_body, access_token);
    return oauth_.Get(request_body.CprUrl(), request_body.CprParameters(),
                      request_body.CprHeader());
}