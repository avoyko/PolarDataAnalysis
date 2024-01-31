#pragma once

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <boost/format.hpp>
#include <utility>

class Parameters {

    using KeyValue = std::pair<const std::string, std::string>;

public:
    Parameters() = default;

    Parameters(const std::initializer_list<KeyValue>& lst) : mp_(lst){};

    auto operator=(const Parameters& other) {
        mp_ = other.mp_;
        return *this;
    }

    auto operator[](const std::string& key) {
        return mp_[key];
    }

    bool Contains(const std::string& key) {
        return mp_.find(key) != mp_.end();
    }

    bool Erase(const std::string& key) {
        if (mp_.find(key) == mp_.end()) {
            return false;
        }
        mp_.erase(key);
        return true;
    }

    bool IsNone(const std::string& key) {
        return mp_[key].empty();
    }

    Parameters& Add(KeyValue field) {
        mp_.insert(field);
        return *this;
    }

    std::string UrlEncode() {
        std::string urlcode;
        for (auto each : mp_) {
            urlcode += each.first + "=" + each.second + "&";
        }
        urlcode.pop_back();
        return urlcode;
    }

    ~Parameters() = default;

private:
    std::unordered_map<std::string, std::string> mp_;
};

template <class Method>
class BaseHTTP {
public:
    BaseHTTP() = default;
    template <typename... Args>
    cpr::Response Request(Args&&... args) {
        return static_cast<Method*>(this)->Request(std::forward(args...));
    }
    ~BaseHTTP() = default;
};

class Get : public BaseHTTP<Get> {
public:
    Get() = default;
    template <typename... Args>
    cpr::Response Request(Args&&... args) {
        return cpr::Get(std::forward(args...));
    }
};

class Post : public BaseHTTP<Get> {
public:
    Post() = default;
    template <typename... Args>
    cpr::Response Request(Args&&... args) {
        return cpr::Post(std::forward(args...));
    }
};

class Put : public BaseHTTP<Get> {
public:
    Put() = default;
    template <typename... Args>
    cpr::Response Request(Args&&... args) {
        return cpr::Put(std::forward(args...));
    }
};

class Delete : public BaseHTTP<Get> {
public:
    Delete() = default;
    template <typename... Args>
    cpr::Response Request(Args&&... args) {
        return cpr::Delete(std::forward(args...));
    }
};