#include "../default_behaviours.h"

void test_func(struct window* window) {
    buffer_setup_text(&window->data_buff->buffer, "Lul");
}

void test_func2(struct window* window) {
    buffer_setup_text(&window->data_buff->buffer, "Lmfao");
}

void default_behaviours_type() {
    struct behaviour behaviour = behaviour_create_empty("Type");

    behaviour_add_bind(&behaviour, (struct key_bind) {
        .call_back = test_func,
        .type = STOPPING_ALL,
        .bind_size = 1,
        .bind = { 'a', 0, 0, 0, 0, 0, 0, 0 }
    });
    
    behaviour_add_bind(&behaviour, (struct key_bind) {
        .call_back = test_func2,
        .type = STOPPING_ALL,
        .bind_size = 1,
        .bind = { 'b', 0, 0, 0, 0, 0, 0, 0 }
    });
    
    default_behaviour_add((struct default_behaviour) {
            .behaviour = behaviour,
            .defaultable = 0,
            .write_func = 0,
            .load_func = 0,
            .ending_match = ""
    });
}
