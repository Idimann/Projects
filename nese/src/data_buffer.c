#include "data_buffer.h"

#include <stdio.h>
#include <string.h>

static struct data_buffer* BUFFERS = NULL;
static size_t BUFFERS_SIZE = 0;

void data_add(struct data_buffer input) {
    ++BUFFERS_SIZE;

    const struct data_buffer* old = BUFFERS;
    BUFFERS = malloc(sizeof(struct data_buffer) * BUFFERS_SIZE);
    memcpy(BUFFERS, old, sizeof(struct data_buffer) * (BUFFERS_SIZE - 1));

    if(old)
        free((void*) old);

    BUFFERS[BUFFERS_SIZE - 1] = input;
}

struct data_buffer* data_get(size_t index) {
    if(index >= BUFFERS_SIZE)
        return NULL; //Should throw an error

    return &(BUFFERS[index]);
}

enum ErrType data_top(struct data_buffer** input) {
    if(BUFFERS_SIZE <= 0)
        return ERR_INDEX;

    *input = &(BUFFERS[BUFFERS_SIZE - 1]);
    return ERR_NONE;
}

static struct default_behaviour* DBEHAVIOURS = NULL;
static size_t DBEHAVIOURS_SIZE = 0;

void default_behaviour_add(struct default_behaviour input) {
    ++DBEHAVIOURS_SIZE;

    const struct default_behaviour* old = DBEHAVIOURS;
    DBEHAVIOURS = malloc(sizeof(struct default_behaviour) * 
            DBEHAVIOURS_SIZE);
    memcpy(DBEHAVIOURS, old, 
            sizeof(struct default_behaviour) * (DBEHAVIOURS_SIZE - 1));

    if(old)
        free((void*) old);

    DBEHAVIOURS[DBEHAVIOURS_SIZE - 1] = input;
}

struct default_behaviour* default_behaviour_get(size_t index) {
    if(index >= DBEHAVIOURS_SIZE)
        return NULL; //Should throw an error

    return &(DBEHAVIOURS[index]);
}

void data_default_behaviours(struct data_buffer* input) {
    for(size_t i = 0; i < DBEHAVIOURS_SIZE; i++) {
        if(!DBEHAVIOURS[i].defaultable)
            continue;

        if(DBEHAVIOURS[i].write_func &&
                DBEHAVIOURS[i].write_func != input->buffer.write_func)
            continue;

        if(DBEHAVIOURS[i].load_func &&
                DBEHAVIOURS[i].load_func != input->buffer.load_func)
            continue;


        const size_t dLen = strlen(DBEHAVIOURS[i].ending_match);
        const size_t bLen = strlen(input->buffer.callback_addr);

        if(dLen > bLen)
            continue;

        if(strncmp(DBEHAVIOURS[i].ending_match,
                    &input->buffer.callback_addr[bLen - dLen], dLen) != 0)
            continue;

        data_add_behaviour(input, DBEHAVIOURS[i].behaviour);
    }
}

void data_callback_behaviours(struct data_buffer* input) {
    for(size_t i = 0; i < (input->behaviour_size); i++) {
        if(input->behaviour_stack[i].call_back)
            input->behaviour_stack[i].call_back(input);
    }
}

struct data_buffer data_create_empty() {
    return (struct data_buffer) {
        .buffer = buffer_create_empty(),
        .remark_stack = NULL,
        .remark_size = 0,
        .behaviour_stack = NULL,
        .behaviour_size = 0
    };
}

void data_add_behaviour(struct data_buffer* input, struct behaviour bh) {
    ++input->behaviour_size;

    struct behaviour* old = input->behaviour_stack;
    input->behaviour_stack = malloc(sizeof(struct behaviour) * 
            input->behaviour_size);
    memcpy(input->behaviour_stack, old, 
            sizeof(struct behaviour) * (input->behaviour_size - 1));

    if(old)
        free((void*) old);

    input->behaviour_stack[input->behaviour_size - 1] = bh;
}

enum ErrType data_full_setup_file(const char* file) {
    struct data_buffer data = data_create_empty();
    const enum ErrType error = data_setup_file(&data, file);

    if(error)
        return error;

    data_default_behaviours(&data);
    data_add(data);

    return ERR_NONE;
}

enum ErrType data_setup_file(struct data_buffer* input, const char* file) {
    const enum ErrType error = buffer_setup_file(&input->buffer, file);

    if(error)
        return error;

    input->remark_stack = NULL;
    input->remark_size = 0;
    input->behaviour_stack = NULL;
    input->behaviour_size = 0;

    return ERR_NONE;
}
