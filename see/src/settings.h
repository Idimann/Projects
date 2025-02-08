#pragma once

#include <stdlib.h>

struct settings {
    size_t x_scroll_pad, y_scroll_pad;
    unsigned char default_mode, background_mode;
};

void settings_refresh();
struct settings* settings_get();
