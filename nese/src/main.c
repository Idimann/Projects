#include <ncurses.h>

#include "window.h"

int main(int argc, char** argv) {
    initscr();
    noecho();
    cbreak();
    if(has_colors()) {
        start_color();
        assume_default_colors(-1, -1);
    }

    window_update_screen_size();

    struct data_buffer main_buff = data_create_empty();

    data_setup_file(&main_buff, "test.txt");
    data_add(main_buff);

    struct window window = window_create_empty();
    window_load_data_buffer(&window, &main_buff);
    const struct dimension screen_size = window_screen_size();
    window_load_curses(&window, newwin(screen_size.y, screen_size.x, 0, 0));

    window_add(window);
    window_draw_all();
    getch();

    window_shutdown();
    endwin();
    return 0;
}
