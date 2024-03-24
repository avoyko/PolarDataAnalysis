#pragma once

#include "utilities.h"

using namespace Utils;

class JsonActivityInfo {
public:
    explicit JsonActivityInfo(wjson activity) : activity_(activity) {};

    int ActivityID();

    int TransactionID();

    std::string Date();

    int Calories();

    int ActiveCalories();

    std::string Duration();

    int Steps();

private:
    const wjson activity_;
};


