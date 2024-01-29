#pragma once

#include <initializer_list>
#include <unordered_map>
#include <string>
#include <utility>

using KeyValue = std::pair<const std::string, std::string>;

class Kwargs {
public:
    Kwargs() = default;

    Kwargs(std::initializer_list<KeyValue> & lst) : mp_(lst){};

    auto operator=(const Kwargs& other){
        mp_ = other.mp_;
        return *this;
    }


    bool Contains(const std::string& key) {
        return mp_.find(key) != mp_.end();
    }

    bool Erase(const std::string& key){
        if (mp_.find(key) == mp_.end()){
            return false;
        }
        mp_.erase(key);
        return true;
    }

    Kwargs& Add(KeyValue field){
        mp_.insert(field);
        return *this;
    }

    ~Kwargs() = default;

private:
    std::unordered_map<std::string, std::string> mp_;
};