#pragma once

#include <uchar.h>
#include <stdlib.h>

struct cursor_pos {
    size_t x, y;
    size_t x_scroll, y_scroll;
    size_t actual_x, actual_x_scroll;
};

struct buffer {
    char* data;
    size_t size;
};

struct global_data {
    unsigned char running;

    struct cursor_pos cursor;

    struct buffer* lines;
    size_t lines_size;

    struct buffer file;
    struct buffer command;
};

void global_data_refresh();
struct global_data* global_data_get();

void global_data_cleanup();

void global_data_load_file(const char*);
void global_data_load();
void global_data_write();
