#pragma once

#include <iostream>
#include <string>
#include <utility>

class CalendarException : public std::exception {
public:
    explicit CalendarException(std::string message) : message_{std::move(message)} {};

    [[nodiscard]] const char *what() const noexcept override {
        return message_.c_str();
    }

private:
    std::string message_;
};