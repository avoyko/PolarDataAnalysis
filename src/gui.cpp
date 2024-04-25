#include "gui.h"
#include "debug.h"

#include <ncurses.h>
#include <string>

void InitialiseStartScreen(ScreenConfig &config) {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    config.screenWidth = COLS;
    config.screenHeight = LINES;

    config.windowWidth = config.screenWidth * 0.8;
    config.windowHeight = config.screenHeight * 0.6;
    config.startX = (config.screenWidth - config.windowWidth) / 2;
    config.startY = (config.screenHeight - config.windowHeight) / 2;
}

void InitialiseMainWindow(ScreenConfig &config) {
    WINDOW *window = newwin(config.windowHeight, config.windowWidth, config.startY, config.startX);
    box(window, 0, 0);

    std::string title = " AI Application ";
    mvwprintw(window, 0, (config.windowWidth - title.size()) / 2, title.c_str());

    std::string welcome_message = (DEVELOPER_MODE == 1) ? "Hello user! Navigate to http://localhost:5002/ to register."
                                                        : "Hello user! Navigate to http://172.17.0.2:5002/ to register";

    mvwprintw(window, config.windowHeight / 4, (config.windowWidth - welcome_message.size()) / 2,
              welcome_message.c_str());
    wrefresh(window);

    config.main_window = window;
}

void InitialiseOptionPanel(const ScreenConfig &config) {
    std::string option1 = "[*] 1. Synchronise database";
    std::string option2 = "[ ] 2. Synchronise and run";
    int padding = (config.windowWidth - option1.length()) / 2;
    mvwprintw(config.main_window, config.windowHeight / 2 + 2, padding, option1.c_str());
    mvwprintw(config.main_window, config.windowHeight / 2 + 4, padding, option2.c_str());
}

std::vector<bool> ActivateOptionsScreen(const ScreenConfig &config) {
    std::string option1 = "[*] 1. Synchronise database";
    std::string option2 = "[ ] 2. Synchronise and run";
    std::vector<bool> options{true, false};
    int choice;
    while ((choice = wgetch(config.main_window)) != 10) {
        switch (choice) {
            case '1':
                options[0] = true;
                mvwprintw(config.main_window, config.windowHeight / 2 + 2, (config.windowWidth - option1.length()) / 2,
                          options[0] ? "[*] 1. Synchronise database" : "[ ] 1. Synchronise database");
                mvwprintw(config.main_window, config.windowHeight / 2 + 4, (config.windowWidth - option1.length()) / 2,
                          options[0] ? "[ ] 2. Synchronise and run" : "[*] 2. Synchronise and run");
                break;
            case '2':
                options[1] = true;
                mvwprintw(config.main_window, config.windowHeight / 2 + 4, (config.windowWidth - option1.length()) / 2,
                          options[1] ? "[*] 2. Synchronise and run" : "[ ] 2. Synchronise and run");
                mvwprintw(config.main_window, config.windowHeight / 2 + 2, (config.windowWidth - option1.length()) / 2,
                          options[1] ? "[ ] 1. Synchronise database" : "[*] 1. Synchronise database");
                break;
            default:
                break;
        }
        wrefresh(config.main_window);
    }
    return options;
}