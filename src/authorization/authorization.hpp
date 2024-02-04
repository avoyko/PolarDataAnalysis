#pragma once

#include <crow/utility.h>
#include <crow/app.h>
#include "crow.h"
#include "../oauth2.hpp"
#include "../accesslink.hpp"

namespace Callback {
constexpr char OAUTHPOINT[] = "/oauth2_callback";
const int PORT = 5002;
}  // namespace Callback

namespace Client {
const std::string CLIENT_ID = "bd3a77a4-0edc-44e5-81a5-309644f0fc9a";
const std::string CLIENT_SECRET = "b854a0ca-2a74-4dde-9196-0c0b1b63110e";
const std::string REDIRECT_URI = "http://localhost:5002/oauth2_callback";
};  // namespace Client

void authorize();

int shutdown(crow::SimpleApp &app);
