#include "behaviour.h"

#include <stdlib.h>
#include <string.h>

struct behaviour behaviour_create_empty(const char* name) {
    return (struct behaviour) {
        .binds = NULL,
        .bind_size = 0,
        .name = name,
        .call_back = NULL
    };
}

void behaviour_add_bind(struct behaviour* input, struct key_bind bind) {
    ++input->bind_size;

    const struct key_bind* old = input->binds;
    input->binds = malloc(sizeof(struct key_bind) * 
            input->bind_size);
    memcpy(input->binds, old, 
            sizeof(struct key_bind) * (input->bind_size - 1));

    if(old)
        free((void*) old);

    input->binds[input->bind_size - 1] = bind;
}
