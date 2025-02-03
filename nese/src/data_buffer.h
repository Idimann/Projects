#pragma once

#include <stdlib.h>

#include "buffer.h"
#include "behaviour.h"
#include "run.h"

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

    struct behaviour** behaviour_stack;
    size_t behaviour_size;
};

struct default_behaviour {
    unsigned char defaultable;
    struct behaviour behaviour;
    enum ErrType (*write_func)(struct buffer*);
    enum ErrType (*load_func)(struct buffer*);
    const char* ending_match;
};

void data_add(struct data_buffer);
struct data_buffer* data_get(size_t);
enum ErrType data_top(struct data_buffer**);

void default_behaviour_add(struct default_behaviour);
struct default_behaviour* default_behaviour_get(size_t);

void data_default_behaviours(struct data_buffer*);
void data_callback_behaviours(struct data_buffer*);

struct data_buffer data_create_empty();

void data_add_behaviour(struct data_buffer*, struct behaviour*);

enum ErrType data_full_setup_file(const char*);
enum ErrType data_setup_file(struct data_buffer*, const char*);
