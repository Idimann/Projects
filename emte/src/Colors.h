#pragma once

#include <iostream>

#define STATUS_BAR_COLOR 1

extern int supportColors();
extern void initColors();

extern void create_curses_color(std::string name, const unsigned short r, const unsigned short g, const unsigned short b);
extern short get_curses_color(std::string name);

extern void create_curses_pair(std::string name, const unsigned short first, const unsigned short second);
extern short get_curses_pair(std::string name);
