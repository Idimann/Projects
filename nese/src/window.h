#pragma once

#include <ncurses.h>

#include "data_buffer.h"
#include "run.h"

struct dimension {
    size_t x, y;
};

struct window {
    struct data_buffer* data_buff;
    WINDOW* window;
};

void window_add(struct window);
struct window* window_get(size_t);

void window_shutdown();
void window_draw_all();

void window_update_screen_size();
struct dimension window_screen_size();

struct window window_create_empty();

void window_load_curses(struct window*, WINDOW*);
void window_load_data_buffer(struct window*, struct data_buffer*);

enum ErrType window_full_setup_fullscreen(struct data_buffer*);

void window_kill(struct window*);
void window_draw(struct window*, size_t);

