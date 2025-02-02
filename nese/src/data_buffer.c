#include "data_buffer.h"

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

struct data_buffer data_create_empty() {
    return (struct data_buffer) {
        .buffer = buffer_create_empty(),
        .remark_stack = NULL,
        .remark_size = 0
    };
}

void data_setup_file(struct data_buffer* input, const char* file) {
    buffer_setup_file(&input->buffer, file);

    input->remark_stack = NULL;
    input->remark_size = 0;
}
