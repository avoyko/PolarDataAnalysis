
#include "users.h"

ReadJson Users::Record(const std::string &access_token, boost::uuids::uuid member_id) {
    WriteJson my_json;
    my_json["member-id"] = boost::uuids::to_string(member_id);
    RequestWrapper request_body{"/users", {}};
    oauth_.PrepareRequest(request_body, access_token);
    ReadJson reg_info =
            PostData(cpr::Body{my_json.dump()}, request_body.CprUrl(), request_body.CprHeader());
    return reg_info;
}

ReadJson Users::Remove(const int user_id, std::string &access_token) {
    RequestWrapper request_body{"/users/" + std::to_string(user_id)};
    oauth_.PrepareRequest(request_body, access_token);
    return DeleteData(request_body.CprUrl(), request_body.CprParameters(),
                      request_body.CprHeader());
}

ReadJson Users::GetInformation(const int user_id, std::string &access_token) {
    RequestWrapper request_body{"/users/" + std::to_string(user_id)};
    oauth_.PrepareRequest(request_body, access_token);
    return oauth_.Get(request_body.CprUrl(), request_body.CprParameters(),
                      request_body.CprHeader());
}