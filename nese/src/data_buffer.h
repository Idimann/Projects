#pragma once

#include <stdlib.h>

#include "buffer.h"

enum remark_type {
    RESET,
    COLOR,
    FONT,
};

struct remark {
    size_t pos;
    unsigned int data;
    enum remark_type type;
};

struct data_buffer {
    struct buffer buffer;

    struct remark* remark_stack;
    size_t remark_size;
};

void data_add(struct data_buffer);
struct data_buffer* data_get(size_t);

struct data_buffer data_create_empty();

void data_setup_file(struct data_buffer*, const char*);
