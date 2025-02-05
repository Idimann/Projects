#include "run.h"

#include <ncurses.h>

#include "globals.h"

static void render() {
    struct global_data* data = global_data_get();

    clear();
    addstr(data->buffer);
    refresh();
}

static int INPUT[8] = {0, 0, 0, 0, 0, 0, 0, 0};
static unsigned char INPUT_SIZE = 0;

static void input() {
    struct global_data* data = global_data_get();

    if(INPUT_SIZE > 8)
        INPUT_SIZE = 0;

    INPUT[INPUT_SIZE++] = getch();

    if(INPUT[0] == 'q')
        data->running = false;
}

void run_main_loop() {
    struct global_data* data = global_data_get();

    while(data->running) {
        render();
        input();
    }
}
