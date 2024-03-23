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
    std::string Join(const std::vector<std::string> &strings, const std::string &delim = ",") {
        return std::accumulate(strings.begin(), strings.end(), std::string(),
                               [&delim](const std::string &x, const std::string &y) {
                                   return x.empty() ? y : x + delim + y;
                               });
    }

    const std::string EMPTY_ENDPOINT;
}
