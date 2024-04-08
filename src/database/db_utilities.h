#pragma once
#include <mysqlx/xdevapi.h>
#include <istream>
#include <frozen/string.h>
#include <crow/json.h>

using ReadJson = crow::json::rvalue;
using WriteJson = crow::json::wvalue;

namespace JsonHelper {
static inline std::string NormalizedString(const std::string &s) {
    return s.substr(1, s.size() - 2);
}

static inline std::string StringValue(const WriteJson &json, const std::string &field) {
    return NormalizedString(json[field].dump());
}

static inline std::string IntValue(const WriteJson &json, const std::string &field) {
    return NormalizedString(json[field].dump());
}

static inline std::string DateValue(const WriteJson &json, const std::string &field) {
    std::string date = json[field].dump();
    return date.substr(0, 10);
}

static inline WriteJson JsonValue(const WriteJson &json, const std::string &field) {
    return json[field];
}
}  // namespace JsonHelper

namespace mysqlx {

static inline std::string get_string_date(const mysqlx::Row &row) {
    mysqlx::bytes data = row[0].getRawBytes();
    const mysqlx::byte *first = data.begin();

    int year = (first[1] << 7) | (first[0] & 0x7f);
    int month = first[2];
    int day = first[3];

    char text[20];
    if (month > 9 && day > 9) {
        sprintf(text, "%i-%i-%i", year, month, day);
    } else if (month > 9){
        sprintf(text, "%i-0%i-%i", year, month, day);
    } else if (day > 9){
        sprintf(text, "%i-%i-0%i", year, month, day);
    } else {
        sprintf(text, "%i-0%i-0%i", year, month, day);
    }
    return text;
}

}  // namespace mysqlx