#pragma once

#define ERROR_CHECK(x) ERROR = x; if(ERROR) goto EXIT

enum ErrType {
    ERR_NONE,
    ERR_UNIMPLEMENTED,
    ERR_IMPOSSIBLE,
    ERR_INDEX,
    ERR_PTR,
    ERR_FILE
};

enum ErrType run_main_loop();
void stop_main_loop();
