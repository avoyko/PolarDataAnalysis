#pragma once

#include <ncurses.h>
#include <vector>

struct ScreenConfig {
    WINDOW *main_window;
    int screenWidth;
    int screenHeight;
    int windowWidth;
    int windowHeight;
    int startX;
    int startY;
};

void InitialiseStartScreen(ScreenConfig &config);

void InitialiseMainWindow(ScreenConfig &config);

void InitialiseOptionPanel(const ScreenConfig &config);

std::vector<bool> ActivateOptionsScreen(const ScreenConfig &config);

void ClearBox(const ScreenConfig &config);

void DisplayLoadingPanel(const ScreenConfig &config, const std::atomic_bool &model_finished);