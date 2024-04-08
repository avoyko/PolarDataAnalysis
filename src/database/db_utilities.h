#pragma once
#include <mysqlx/xdevapi.h>
#include <istream>
#include <frozen/string.h>
#include <crow/json.h>

using ReadJson = crow::json::rvalue;
using WriteJson = crow::json::wvalue;

namespace mysqlx {
const std::string DEFAULT_STRING = "NULL";
const std::string DEFAULT_INT = "-1";
const std::string DEFAULT_DATE = "2000-01-01";

static inline std::string get_string_date(const mysqlx::Row &row) {
    mysqlx::bytes data = row[0].getRawBytes();
    const mysqlx::byte *first = data.begin();

    int year = (first[1] << 7) | (first[0] & 0x7f);
    int month = first[2];
    int day = first[3];

    char text[20];
    if (month > 9 && day > 9) {
        sprintf(text, "%i-%i-%i", year, month, day);
    } else if (month > 9) {
        sprintf(text, "%i-0%i-%i", year, month, day);
    } else if (day > 9) {
        sprintf(text, "%i-%i-0%i", year, month, day);
    } else {
        sprintf(text, "%i-0%i-0%i", year, month, day);
    }
    return text;
}

template <typename... Args>
static inline bool IsValidRow(const std::string &date, Args &&...args) {
    return date == DEFAULT_DATE;
}

}  // namespace mysqlx

namespace JsonHelper {

static inline std::vector<std::string> GetDefaultExercises() {
    return {mysqlx::DEFAULT_DATE,   mysqlx::DEFAULT_STRING, mysqlx::DEFAULT_STRING,
            mysqlx::DEFAULT_STRING, mysqlx::DEFAULT_STRING, mysqlx::DEFAULT_STRING,
            mysqlx::DEFAULT_STRING, mysqlx::DEFAULT_STRING, mysqlx::DEFAULT_STRING,
            mysqlx::DEFAULT_STRING, mysqlx::DEFAULT_STRING};
}

static inline std::string NormalizedString(const std::string &s) {
    return s.substr(1, s.size() - 2);
}

static inline std::string StringValue(const WriteJson &json, const std::string &field) {
    if (json[field].dump() == "null") {
        return mysqlx::DEFAULT_STRING;
    }
    return NormalizedString(json[field].dump());
}

static inline std::string IntValue(const WriteJson &json, const std::string &field) {
    if (json[field].dump() == "null") {
        return mysqlx::DEFAULT_INT;
    }
    return NormalizedString(json[field].dump());
}

static inline std::string DateValue(const WriteJson &json, const std::string &field) {
    if (json[field].dump() == "null") {
        return mysqlx::DEFAULT_DATE;
    }
    std::string date = json[field].dump();
    return date.substr(1, 10);
}

static inline WriteJson JsonValue(const WriteJson &json, const std::string &field) {
    return json[field];
}
}  // namespace JsonHelper
