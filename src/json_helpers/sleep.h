#pragma once

#include "utilities.h"

using namespace Utils;

class JsonSleepInfo{
public:
    explicit JsonSleepInfo(wjson sleep): sleep_(std::move(sleep)){};


private:
    const wjson sleep_;
};

