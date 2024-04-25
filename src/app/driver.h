#pragma once

#include <crow/app.h>
#include <yaml-cpp/yaml.h>
#include "../database/include/db_worker.h"
#include "../polar_api/include/accesslink.h"
#include "../debug.h"


/// SET DEVELOPER_MODE TO 0 WHEN EXPORTING TO DOCKER

namespace Callback {
constexpr char OAUTHPOINT[] = "/oauth2_callback";
constexpr char DATAPOINT[] = "/data";
const int PORT = 5002;
}  // namespace Callback

namespace Client {
const std::string CLIENT_ID = "bd3a77a4-0edc-44e5-81a5-309644f0fc9a";
const std::string CLIENT_SECRET = "b854a0ca-2a74-4dde-9196-0c0b1b63110e";

#if (DEVELOPER_MODE == 1)
const std::string REDIRECT_URI = "http://localhost:5002/oauth2_callback";
const std::string DATA_URI = "http://localhost:5002/data";
#else
const std::string REDIRECT_URI = "http://172.17.0.2:5002/oauth2_callback";
const std::string DATA_URI = "http://172.17.0.2:5002/data";
#endif
};  // namespace Client

using HtmlPage = crow::mustache::rendered_template;

class PolarApp {
public:

    int Activate();

    crow::response Authorize(const crow::request &req);

    HtmlPage ProcessData();

private:
    YAML::Node UpdateAccessConfig(const ReadJson &token_response);
};
