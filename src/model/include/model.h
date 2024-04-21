#pragma once

#include <string>
#include <vector>

class Model {
public:
    void Activate();

    std::vector<std::string> GetPrediction();
};