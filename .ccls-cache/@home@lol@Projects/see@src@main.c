#include <signal.h>
#include <ncurses.h>

#include "settings.h"
#include "globals.h"
#include "run.h"

int main(int argc, char** argv) {
    if(argc != 2) {
        printf("Usage: see <filename>\n\n");
        return 2;
    }

    signal(SIGINT, SIG_IGN);

    initscr();
    noecho();
    cbreak();
    if(has_colors()) {
        start_color();
        assume_default_colors(-1, -1);
    }

    settings_refresh();

    global_data_refresh();
    global_data_load_file(argv[1]);
    global_data_load();

    run_main_loop();

    global_data_cleanup();
    endwin();
    return 0;
}
