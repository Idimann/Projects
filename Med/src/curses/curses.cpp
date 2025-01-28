#include "curses.h"
#include <curses.h>

extern void initNcurses() {
    initscr();
    noecho();
    cbreak();
    clear();
    curs_set(0);
    start_color();
    use_default_colors();
    init_pair(0, COLOR_WHITE, COLOR_BLACK);
}

extern void quitNcurses() {
    clear();
    endwin();
    exit(0);
}
