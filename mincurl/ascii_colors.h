#pragma once
#include <Windows.h>
#include <iostream>

#define RESET_TEXT "\033[0m"

#define START_GREEN "\033[32m"
#define START_RED "\033[31m"
#define START_CYAN "\033[36m"

#define GREEN_TEXT(text) START_GREEN text RESET_TEXT
#define RED_TEXT(text) START_RED text RESET_TEXT
#define CYAN_TEXT(text) START_CYAN text RESET_TEXT

void InitAsciiConsole() {
    // Enable support for ANSI escape codes in Windows console
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}
void PrintColoredText(const std::string text, const char color, bool showIcon) {
    switch (color) {
    case 'r':
        std::cout << START_RED;
        if (showIcon) {
            std::cout << "[-]";
        }
        break;

    case 'g':
        std::cout << START_GREEN;
        if (showIcon) {
            std::cout << "[+]";
        }
        break;

    case 'c':
        std::cout << START_CYAN;
        if (showIcon) {
            std::cout << "[|]";
        }
        break;

    default: return;
    }

    std::cout << text.c_str();
    std::cout << RESET_TEXT;
}