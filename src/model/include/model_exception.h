#pragma once

#include <iostream>
#include <string>
#include <utility>

class ModelException : public std::exception {
public:
    explicit ModelException(std::string message) : message_{std::move(message)} {};

    [[nodiscard]] const char *what() const noexcept override {
        return message_.c_str();
    }

private:
    std::string message_;
};