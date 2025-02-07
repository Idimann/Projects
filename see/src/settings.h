#pragma once

#include <stdlib.h>

struct settings {
    size_t x_scroll_pad, y_scroll_pad;
};

void settings_refresh();
struct settings* settings_get();
