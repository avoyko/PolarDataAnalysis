#pragma once

#include <crow/app.h>
#include <yaml-cpp/yaml.h>
#include "database/db.h"
#include "polar_api/accesslink.h"

namespace Callback {
constexpr char OAUTHPOINT[] = "/oauth2_callback";
constexpr char DATAPOINT[] = "/data";
const int PORT = 5002;
}  // namespace Callback

namespace Client {
const std::string CLIENT_ID = "bd3a77a4-0edc-44e5-81a5-309644f0fc9a";
const std::string CLIENT_SECRET = "b854a0ca-2a74-4dde-9196-0c0b1b63110e";
const std::string REDIRECT_URI = "http://localhost:5002/oauth2_callback";
const std::string DATA_URI = "http://localhost:5002/data";
};  // namespace Client

class PolarApp {
public:
    static int Activate();

private:
    static crow::response Authorize(const crow::request &req);

    static crow::mustache::rendered_template ProcessData();

    static YAML::Node UpdateAccessConfig(const rjson &token_response);
};
