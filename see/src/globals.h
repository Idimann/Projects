#pragma once

#include <uchar.h>
#include <stdlib.h>

struct cursor_pos {
    size_t x, y;
};

struct global_data {
    unsigned char running;

    struct cursor_pos cursor_pos;

    char* buffer;
    size_t buffer_size;

    char* file;
    size_t file_size;

    char* command;
    size_t command_size;
};

void global_data_refresh();
struct global_data* global_data_get();

void global_data_cleanup();

void global_data_load_file(const char*);
void global_data_load();
void global_data_write();
