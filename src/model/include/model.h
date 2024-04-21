#pragma once

#include <string>

class Model {
public:
    void Activate();

    std::vector<std::string> GetPrediction();
};