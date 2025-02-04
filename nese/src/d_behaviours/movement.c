#include "../default_behaviours.h"

void default_behaviours_movement() {
    struct behaviour behaviour = behaviour_create_empty("Move");

    default_behaviour_add((struct default_behaviour) {
            .behaviour = behaviour,
            .defaultable = 0,
            .write_func = 0,
            .load_func = 0,
            .ending_match = ""
    });
}
