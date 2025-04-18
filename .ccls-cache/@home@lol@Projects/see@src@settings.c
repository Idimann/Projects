#include "settings.h"

struct settings* SETTINGS = NULL;

void settings_refresh() {
    SETTINGS = malloc(sizeof(struct settings));

    *SETTINGS = (struct settings) {
        .x_scroll_pad = 2,
        .y_scroll_pad = 4,
        .default_mode = '\t',
        .background_mode = '\0',
    };
}

struct settings* settings_get() {
    return SETTINGS;
}
