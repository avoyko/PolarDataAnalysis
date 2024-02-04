#include "crow.h"

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([]() { return "Hello world"; });

    // set the port, set the app to run on multiple threads, and run the app
    app.port(5001).multithreaded().run();
}