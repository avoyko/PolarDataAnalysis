#pragma once

#include <cpr/cpr.h>
#include <cstddef>
#include <initializer_list>
#include <nlohmann/json.hpp>
#include <boost/format.hpp>
#include <utility>
#include <cpr/parameters.h>
#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid.hpp>             // uuid class
#include <boost/uuid/uuid_generators.hpp>  // generators
#include <boost/uuid/uuid_io.hpp>          // streaming operators etc.
#include <boost/beast/core/detail/base64.hpp>

using json = nlohmann::json;
using ParsedResponse = json;
using Authentication = cpr::Authentication;
using Response = cpr::Response;
using Headers = cpr::Header;
using Body = cpr::Body;
using Payload = cpr::Payload;
using Parameters = cpr::Parameters;

namespace Utils {
    const std::string EMPTY_ENDPOINT;
}
