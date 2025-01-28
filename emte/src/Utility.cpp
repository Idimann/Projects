#include <curses.h>
#include <functional>
#include <sys/ioctl.h>
#include <ncurses.h>
#include <iostream>
#include <string>
#include "Utility.h"
#include "Colors.h"

extern int clampInt(const int value, const int min, const int max) {
    return value < min ? min : (value > max ? max : value);
}

extern int minInt(const int first, const int second) {
    return first < second ? first : second;
}

extern std::string replaceAll(std::string str, const std::string from, const std::string to) {
    if(from.empty())
        return str;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }

    return str;
}

extern std::string createMultiChar(const char character, const int number) {
    std::string returning = "";
    returning.append(number, character);

    return returning;
}

extern void init() {
    initscr();
    noecho();
    cbreak();
    clear();
    //curs_set(0);
    initColors();
}
