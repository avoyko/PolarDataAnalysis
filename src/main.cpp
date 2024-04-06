#include <iostream>

#include "app/driver.h"

int main() {
    try {
        PolarApp polar_app;
        return polar_app.Activate();
    } catch (const std::exception& exception) {
        std::cerr << exception.what() << std::endl;
        return -1;
    } catch (...) {
        return -2;
    }
}