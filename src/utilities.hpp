#pragma once

#include "cpr/cpr.h"
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

namespace Utils {
    const std::string EMPTY_ENDPOINT;
}


class QueryArgs {
    using KeyValue = std::pair<const std::string, std::string>;

public:
    QueryArgs() = default;

    ~QueryArgs() = default;

    QueryArgs(std::initializer_list<KeyValue> lst) : mp_(lst) {};

    QueryArgs &operator=(const QueryArgs &other) = default;

    std::string &operator[](const std::string &key) {
        return mp_[key];
    }

    std::string operator[](const std::string &key) const {
        return mp_.at(key);
    }

    QueryArgs &Add(const KeyValue &field) {
        mp_.insert(field);
        return *this;
    }

    bool Contains(const std::string &key) {
        return mp_.find(key) != mp_.end();
    }

    bool Erase(const std::string &key) {
        if (mp_.find(key) == mp_.end()) {
            return false;
        }
        mp_.erase(key);
        return true;
    }

    bool IsNone(const std::string &key) {
        return mp_[key].empty();
    }

    cpr::Parameters ConvertToCpr() {
        cpr::Parameters parameters;
        for (const auto &each: mp_) {
            if (each.first == "url") {
                continue;
            }
            parameters.Add({each.first, each.second});
        }
        return parameters;
    }

    std::string UrlEncode() {
        std::string url_code;
        for (const auto &each: mp_) {
            url_code += each.first + "=" + each.second + "&";
        }
        url_code.pop_back();
        return url_code;
    }

private:
    std::unordered_map<std::string, std::string> mp_;
};

class GetRequest {
public:
    GetRequest() = default;

    template<typename... Args>
    cpr::Response MakeRequest(Args &&... args) {
        return cpr::Get(std::forward<Args>(args)...);
    }
};

class PostRequest {
public:
    PostRequest() = default;

    template<typename... Args>
    cpr::Response MakeRequest(Args &&... args) {
        return cpr::Post(std::forward<Args>(args)...);
    }
};

class PutRequest {
public:
    PutRequest() = default;

    template<typename... Args>
    cpr::Response MakeRequest(Args &&... args) {
        return cpr::Put(std::forward<Args>(args)...);
    }
};

class DeleteRequest {
public:
    DeleteRequest() = default;

    template<typename... Args>
    cpr::Response MakeRequest(Args &&... args) {
        return cpr::Delete(std::forward<Args>(args)...);
    }
};