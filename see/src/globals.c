#include "globals.h"

#include <stdio.h>
#include <string.h>

static struct global_data* GLOBAL = NULL;

void global_data_refresh() {
    if(!GLOBAL)
        GLOBAL = malloc(sizeof(struct global_data));

    *GLOBAL = (struct global_data) {
        .running = 1,

        .cursor_pos = (struct cursor_pos) {
            .x = 0,
            .y = 0
        },

        .buffer = NULL,
        .buffer_size = 0,

        .file = NULL,
        .file_size = 0,

        .command = NULL,
        .command_size = 0
    };
}

struct global_data* global_data_get() {
    return GLOBAL;
}

void global_data_cleanup() {
    if(!GLOBAL)
        return;

    free(GLOBAL->buffer);
    free(GLOBAL->file);
    free(GLOBAL->command);

    free(GLOBAL);
    GLOBAL = 0;
}

void global_data_load_file(const char* file) {
    GLOBAL->file_size = strlen(file) + 1;
    GLOBAL->file = malloc(GLOBAL->file_size);
    strcpy(GLOBAL->file, file);
}

void global_data_load() {
    FILE* f = fopen(GLOBAL->file, "r");

    if(!f)
        return;

    fseek(f, 0L, SEEK_END);
    GLOBAL->buffer_size = ftell(f);
    rewind(f);

    if(GLOBAL->buffer_size) {
        GLOBAL->buffer = malloc(sizeof(char) * GLOBAL->buffer_size);

        fread(GLOBAL->buffer, sizeof(char), GLOBAL->buffer_size, f);
    }

    fclose(f);
}

void global_data_write() {
    FILE* f = fopen(GLOBAL->file, "w+");

    fwrite(GLOBAL->buffer, GLOBAL->buffer_size, sizeof(char), f);
    fclose(f);
}
