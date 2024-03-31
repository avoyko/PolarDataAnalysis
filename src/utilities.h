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
#include <mysqlx/xdevapi.h>
#include <istream>

using rjson = crow::json::rvalue;
using wjson = crow::json::wvalue;
using ParsedResponse = rjson;
using Authentication = cpr::Authentication;
using Response = cpr::Response;
using Headers = cpr::Header;
using Body = cpr::Body;
using Payload = cpr::Payload;
using Parameters = cpr::Parameters;


namespace StringHelper {

template <class Container>
static std::string Join(const Container &strings, const std::string &delim = ",") {
    return std::accumulate(strings.begin(), strings.end(), std::string(),
                           [&delim](const std::string &x, const std::string &y) {
                               return x.empty() ? y : x + delim + y;
                           });
}
}  // namespace StringHelper

namespace JsonHelper {
static inline std::string NormalizedString(const std::string &s) {
    return s.substr(1, s.size() - 2);
}

static inline std::string StringValue(const wjson &json, const std::string &field) {
    return NormalizedString(json[field].dump());
}

static inline std::string IntValue(const wjson &json, const std::string &field) {
    return NormalizedString(json[field].dump());
}

static inline std::string DateValue(const wjson &json, const std::string &field) {
    std::string date = json[field].dump();
    return date.substr(0, 10);
}

static inline wjson JsonValue(const wjson &json, const std::string &field) {
    return json[field];
}
}  // namespace JsonHelper

namespace mysqlx {

static inline std::vector<uint64_t> mysqlx_raw_as_u64_vector(const mysqlx::Value &in_value) {
    std::vector<uint64_t> out;

    const auto bytes = in_value.getRawBytes();
    auto ptr = reinterpret_cast<const std::byte *>(bytes.first);
    auto end = reinterpret_cast<const std::byte *>(bytes.first) + bytes.second;

    while (ptr != end) {
        static constexpr std::byte carry_flag{0b1000'0000};
        static constexpr std::byte value_mask{0b0111'1111};

        uint64_t v = 0;
        uint64_t shift = 0;
        bool is_carry;
        do {
            auto byte = *ptr;
            is_carry = (byte & carry_flag) == carry_flag;
            v |= std::to_integer<uint64_t>(byte & value_mask) << shift;

            ++ptr;
            shift += 7;
        } while (is_carry && ptr != end && shift <= 63);

        out.push_back(v);
    }

    return out;
}

static inline std::chrono::year_month_day read_date(const mysqlx::Value &value) {
    const auto vector = mysqlx_raw_as_u64_vector(value);
    if (vector.size() < 3)
        throw std::out_of_range{"Value is not a valid DATE"};

    return std::chrono::year{static_cast<int>(vector.at(0))} / static_cast<int>(vector.at(1)) /
           static_cast<int>(vector.at(2));
}

static inline std::string get_string_date(const mysqlx::Row &row) {
    mysqlx::bytes data = row[0].getRawBytes();
    const mysqlx::byte *first = data.begin();

    int year = (first[1] << 7) | (first[0] & 0x7f);
    int month = first[2];
    int day = first[3];

    char text[20];
    if (month > 9) {
        sprintf(text, "%i-%i-%i", year, month, day);
    } else {
        sprintf(text, "%i-0%i-%i", year, month, day);
    }
    return text;
}
}  // namespace mysqlx