#include "Colors.h"
#include <ncurses.h>
#include <iostream>
#include <map>

int colorSupport = 0;
std::map<std::string, short> color_map = std::map<std::string, short>();
std::map<std::string, short> pair_map = std::map<std::string, short>();
unsigned short color_map_counter = 16;
unsigned short pair_map_counter = 1;

extern void create_curses_color(std::string name, const unsigned short r, const unsigned short g, const unsigned short b) {
    init_color(color_map_counter, r, g, b);
    color_map[name] = color_map_counter;
    ++color_map_counter;
}

extern void create_curses_pair(std::string name, const unsigned short first, const unsigned short second) {
    init_pair(pair_map_counter, first, second);
    pair_map[name] = pair_map_counter;

    ++pair_map_counter;
}

extern short get_curses_color(std::string name) {
    return color_map[name];
}

extern short get_curses_pair(std::string name) {
    return COLOR_PAIR(pair_map[name]);
}

extern void initColors() {
    colorSupport = (has_colors() | COLORS);
    if(!colorSupport)
        return;

    start_color();
    use_default_colors();

    create_curses_color("Status bar", 204, 167, 167);
    create_curses_pair("Status bar", COLOR_BLUE, get_curses_color("Status bar"));
}

extern int supportColors() {
    return colorSupport;
}
