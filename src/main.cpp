#include <iostream>

#include "app/driver.h"
#include <filesystem>

int main(int argc, char **argv) {
    try {
        PolarApp polar_app;
        return polar_app.Activate();
    } catch (const std::exception &exception) {
        std::cerr << exception.what() << std::endl;
        return -1;
    } catch (...) {
        return -2;
    }
}