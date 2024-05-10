#include "gui.h"
#include "debug.h"

#include <ncurses.h>
#include <string>
#include <thread>

void InitialiseStartScreen(ScreenConfig &config) {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    config.screenWidth = COLS;
    config.screenHeight = LINES;

    config.windowWidth = config.screenWidth * 0.8;
    config.windowHeight = config.screenHeight * 0.7;
    config.startX = (config.screenWidth - config.windowWidth) / 2;
    config.startY = (config.screenHeight - config.windowHeight) / 2;
}

void InitialiseMainWindow(ScreenConfig &config) {
    WINDOW *window = newwin(config.windowHeight, config.windowWidth, config.startY, config.startX);
    box(window, 0, 0);

    std::string title = " AI Application ";
    mvwprintw(window, 0, (config.windowWidth - title.size()) / 2, title.c_str());

    std::string welcome_message = "Hello user! Navigate to http://localhost:5002/ to register.";

    mvwprintw(window, config.windowHeight / 4, (config.windowWidth - welcome_message.size()) / 2,
              welcome_message.c_str());
    wrefresh(window);

    config.main_window = window;
}

void InitialiseOptionPanel(const ScreenConfig &config) {
    std::string option1 = "[*] 1. Synchronise and start working";
    std::string option2 = "[ ] 2. Exit";
    std::string message = "Choose one option and press Enter to continue";
    int option_padding = (config.windowWidth - option1.size()) / 2;
    mvwprintw(config.main_window, config.windowHeight / 2, (config.windowWidth - message.size()) / 2, message.c_str());
    mvwprintw(config.main_window, config.windowHeight / 2 + 2, option_padding, option1.c_str());
    mvwprintw(config.main_window, config.windowHeight / 2 + 4, option_padding, option2.c_str());
}

std::vector<bool> ActivateOptionsScreen(const ScreenConfig &config) {
    std::string option1 = "[*] 1. Synchronise and start working";
    std::string option2 = "[ ] 2. Exit";
    std::vector<bool> options{true, false};
    int choice;
    while ((choice = wgetch(config.main_window)) != 10) {
        switch (choice) {
            case '1':
                options[0] = true;
                options[1] = false;
                mvwprintw(config.main_window, config.windowHeight / 2 + 2, (config.windowWidth - option1.length()) / 2,
                          "[*] 1. Synchronise and start working");
                mvwprintw(config.main_window, config.windowHeight / 2 + 4, (config.windowWidth - option1.length()) / 2,
                          "[ ] 2. Exit");
                break;
            case '2':
                options[1] = true;
                options[0] = false;
                mvwprintw(config.main_window, config.windowHeight / 2 + 4, (config.windowWidth - option1.length()) / 2,
                          "[*] 2. Exit");
                mvwprintw(config.main_window, config.windowHeight / 2 + 2, (config.windowWidth - option1.length()) / 2,
                          "[ ] 1. Synchronise and start working");
                break;
            default:
                break;
        }
        wrefresh(config.main_window);
    }
    return options;
}

void ClearBox(const ScreenConfig &config) {
    wclear(config.main_window);
    box(config.main_window, 0, 0);

    std::string title = " AI Application ";
    mvwprintw(config.main_window, 0, (config.windowWidth - title.size()) / 2, title.c_str());
    wrefresh(config.main_window);
}

void DisplayLoadingPanel(const ScreenConfig &config, const std::atomic_bool &model_finished) {
    std::string msg = "Waiting";
    int padding = (config.windowWidth - msg.size()) / 2;
    while (!model_finished) {
        for (int i = 0; i < 3; ++i) {
            msg.push_back('.');
            mvwprintw(config.main_window, config.windowHeight / 4, padding, msg.c_str());
            wrefresh(config.main_window);
            std::this_thread::sleep_for(std::chrono::milliseconds(2 * 1000));
        }
        ClearBox(config);
        msg = "Waiting";
    }
}