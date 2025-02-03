#include "run.h"
#include "window.h"

enum ErrType runMainLoop() {
    window_draw_all();
    getch();

    return ERR_NONE;
}
