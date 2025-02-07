#include "run.h"

#include <ncurses.h>

#include "globals.h"
#include "input.h"

static void render() {
    struct global_data* data = global_data_get();

    clear();

    int x_size, y_size;
    getmaxyx(stdscr, y_size, x_size);

    for(size_t i = data->cursor.y_scroll; i < (data->lines_size) &&
            i < y_size - data->cursor.y_scroll; i++) {

        if(data->lines[i].size > data->cursor.x_scroll + 1)
            addnstr(&(data->lines[i].data[data->cursor.x_scroll]), x_size);
    }

    move(data->cursor.y - data->cursor.y_scroll, data->cursor.x - data->cursor.x_scroll);
    refresh();
}

static int INPUT[8] = {0, 0, 0, 0, 0, 0, 0, 0};
static unsigned char INPUT_SIZE = 0;

static void input() {
    if(INPUT_SIZE > 7)
        INPUT_SIZE = 0;

    INPUT[INPUT_SIZE++] = getch();

    if(!input_process(INPUT, INPUT_SIZE))
        INPUT_SIZE = 0;
}

void run_main_loop() {
    struct global_data* data = global_data_get();

    while(data->running) {
        render();
        input();
    }
}
