#include <ncurses.h>

#include "window.h"
#include "run.h"

int main(int argc, char** argv) {
    initscr();
    noecho();
    cbreak();
    if(has_colors()) {
        start_color();
        assume_default_colors(-1, -1);
    }

    enum ErrType ERROR = ERR_NONE;

    window_update_screen_size();

    if(argc != 2) {
        ERROR_CHECK(ERR_UNIMPLEMENTED);
    }
    else {
        ERROR_CHECK(data_full_setup_file(argv[1]));
        struct data_buffer* top_buff = NULL;
        ERROR_CHECK(data_top(&top_buff));
        ERROR_CHECK(window_full_setup_fullscreen(top_buff));
    }

    ERROR_CHECK(runMainLoop());

EXIT:
    window_shutdown();
    endwin();

    if(ERROR) {
        switch(ERROR) {
            case ERR_NONE:
                break;
            case ERR_UNIMPLEMENTED:
                fprintf(stderr, "Exited with unimplemented error\n");
                break;
            case ERR_IMPOSSIBLE:
                fprintf(stderr, "Exited with impossible error\n");
                break;
            case ERR_INDEX:
                fprintf(stderr, "Exited with index error\n");
                break;
            case ERR_PTR:
                fprintf(stderr, "Exited with pointer error\n");
                break;
            case ERR_FILE:
                fprintf(stderr, "Exited with file error\n");
                break;
        }
    }

    return 0;
}
