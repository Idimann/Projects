#include "globals.h"

#include <stdio.h>
#include <string.h>

static struct global_data* GLOBAL = NULL;

void global_data_refresh() {
    if(!GLOBAL)
        GLOBAL = malloc(sizeof(struct global_data));

    *GLOBAL = (struct global_data) {
        .running = 1,

        .cursor = {
            .x = 0,
            .y = 0,
            .x_scroll = 0,
            .y_scroll = 0,
            .actual_x = 0,
            .actual_x_scroll = 0
        },

        .lines = NULL,
        .lines_size = 0,

        .file = {
            .data = NULL,
            .size = 0
        },

        .command = {
            .data = NULL,
            .size = 0
        }
    };
}

struct global_data* global_data_get() {
    return GLOBAL;
}

void global_data_cleanup() {
    if(!GLOBAL)
        return;

    for(size_t i = 0; i < (GLOBAL->lines_size); i++)
        free(GLOBAL->lines[i].data);

    free(GLOBAL->lines);
    free(GLOBAL->file.data);
    free(GLOBAL->command.data);

    free(GLOBAL);
    GLOBAL = 0;
}

void global_data_load_file(const char* file) {
    GLOBAL->file.size = strlen(file) + 1;
    GLOBAL->file.data = malloc(GLOBAL->file.size);
    strcpy(GLOBAL->file.data, file);
}

#define BUF_SIZE 65536

static size_t count_lines(FILE* file) { //Copied from StackOverflow
    char buf[BUF_SIZE];
    int counter = 0;
    for(;;)
    {
        size_t res = fread(buf, 1, BUF_SIZE, file);
        if (ferror(file))
            return -1;

        int i;
        for(i = 0; i < res; i++)
            if (buf[i] == '\n')
                counter++;

        if (feof(file))
            break;
    }

    return counter;
}

#define LINE_BUFF_SIZE 2048

void global_data_load() {
    FILE* f = fopen(GLOBAL->file.data, "r");

    if(!f)
        return;

    GLOBAL->lines_size = count_lines(f);
    GLOBAL->lines = malloc(sizeof(struct buffer) * GLOBAL->lines_size);
    rewind(f);

    char buff[LINE_BUFF_SIZE];
    for(size_t i = 0; i < (GLOBAL->lines_size); i++) {
        if(!fgets(buff, LINE_BUFF_SIZE, f))
            break;

        GLOBAL->lines[i].size = strlen(buff) + 1;
        GLOBAL->lines[i].data = malloc(sizeof(char) * GLOBAL->lines[i].size);
        memcpy(GLOBAL->lines[i].data, buff, GLOBAL->lines[i].size);
    }

    if(f)
        fclose(f);
}

void global_data_write() {
    FILE* f = fopen(GLOBAL->file.data, "w+");

    for(size_t i = 0; i < (GLOBAL->lines_size); i++)
        fputs(GLOBAL->lines[i].data, f);

    fclose(f);
}
