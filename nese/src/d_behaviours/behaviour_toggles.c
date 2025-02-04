#include "../default_behaviours.h"

#include <string.h>

static void toggle_type(struct window* window) {
    const struct behaviour bh = default_behaviour_get(2)->behaviour;
    const size_t len = strlen(bh.name);

    int rToggle = 0;
    size_t removing = 0;
    for(size_t i = 0; i < window->data_buff->behaviour_size; i++) {
        if(strlen(window->data_buff->behaviour_stack[i].name) != len)
            continue;

        if(strncmp(window->data_buff->behaviour_stack[i].name,
                    bh.name, len) == 0) {
            removing = i;
            rToggle = 1;
        }
    }

    if(rToggle) {
        --window->data_buff->behaviour_size;

        struct behaviour* old = window->data_buff->behaviour_stack;
        window->data_buff->behaviour_stack = malloc(
            sizeof(struct behaviour) * window->data_buff->behaviour_size);

        if(removing)
            memcpy(window->data_buff->behaviour_stack, old,
                    sizeof(struct behaviour) * removing);

        if(removing != window->data_buff->behaviour_size)
            memcpy(&window->data_buff->behaviour_stack[removing],
                    &old[removing + 1], sizeof(struct behaviour) *
                    (window->data_buff->behaviour_size - removing));

        if(old)
            free(old);
    }
    else {
        ++window->data_buff->behaviour_size;

        struct behaviour* old = window->data_buff->behaviour_stack;
        window->data_buff->behaviour_stack = malloc(
            sizeof(struct behaviour) * window->data_buff->behaviour_size);
        memcpy(window->data_buff->behaviour_stack, old,
            sizeof(struct behaviour) * window->data_buff->behaviour_size);

        window->data_buff->behaviour_stack[window->data_buff->behaviour_size
            - 1] = bh;

        if(old)
            free(old);
    }
}

static void toggle_movement(struct window* window) {
    
}

void default_behaviours_behaviour_toggles() {
    struct behaviour behaviour = behaviour_create_empty("Default");

    behaviour_add_bind(&behaviour, (struct key_bind) {
        .call_back = toggle_type,
        .type = STOPPING_ALL,
        .bind_size = 1,
        .bind = { CTRL('t'), 0, 0, 0, 0, 0, 0, 0 }
    });
    
    behaviour_add_bind(&behaviour, (struct key_bind) {
        .call_back = toggle_movement,
        .type = STOPPING_ALL,
        .bind_size = 1,
        .bind = { CTRL(' '), 0, 0, 0, 0, 0, 0, 0 }
    });

    default_behaviour_add((struct default_behaviour) {
            .behaviour = behaviour,
            .defaultable = 1,
            .write_func = 0,
            .load_func = 0,
            .ending_match = ""
    });
}
