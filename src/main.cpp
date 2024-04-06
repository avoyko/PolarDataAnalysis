#include <iostream>

#include "app/driver.h"

int main() {
    try {

        return PolarApp::Activate();
    } catch (const std::exception& exception) {
        std::cerr << exception.what() << std::endl;
        return -1;
    } catch (...) {
        return -2;
    }
}