#pragma once

#include <cpr/cpr.h>
#include <cstddef>
#include <initializer_list>
#include <boost/format.hpp>
#include <utility>
#include <cpr/parameters.h>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid.hpp>             // uuid class
#include <boost/uuid/uuid_generators.hpp>  // generators
#include <boost/uuid/uuid_io.hpp>          // streaming operators etc.
#include <boost/beast/core/detail/base64.hpp>
#include <crow.h>

using rjson = crow::json::rvalue;
using wjson = crow::json::wvalue;
using ParsedResponse = rjson;
using Authentication = cpr::Authentication;
using Response = cpr::Response;
using Headers = cpr::Header;
using Body = cpr::Body;
using Payload = cpr::Payload;
using Parameters = cpr::Parameters;

namespace Utils {

const std::string EMPTY_ENDPOINT;
}

namespace JsonHelper {
static std::string NormalizedString(const std::string &s) {
    return s.substr(1, s.size() - 2);
}

static std::string StringValue(const wjson &json, const std::string &field) {
    std::cout << json[field].dump()<<'\n';
    return NormalizedString(json[field].dump());
}

static std::string IntValue(const wjson &json, const std::string &field) {
    return NormalizedString(json[field].dump());
}

static wjson JsonValue(const wjson &json, const std::string &field) {
    return json[field];
}
}  // namespace JsonHelper