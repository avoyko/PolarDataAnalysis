#pragma once

#include <initializer_list>
#include <unordered_map>
#include <string>
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

/// handfull wrapper of boost::format
class Formatter {
public:
private:
};