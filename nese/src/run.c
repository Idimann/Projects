#include "run.h"
#include "window.h"

int running = 1;

enum ErrType run_main_loop() {
    enum ErrType ERROR = ERR_NONE;

    while(running) {
        window_draw_all();
        ERROR_CHECK(window_process_input());
    }

EXIT:
    return ERROR;
}

void stop_main_loop() {
    running = 0;
}
