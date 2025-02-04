#pragma once

#include <stddef.h>

enum key_bind_type {
    STOPPING_ALL,
    TRANSMITTING,
    STOPPING_BEHAVIOUR
};

struct window;

struct key_bind {
    unsigned char bind_size;
    int bind[8];
    enum key_bind_type type;
    void (*call_back)(struct window*);
};

struct data_buffer;

struct behaviour {
    struct key_bind* binds;
    size_t bind_size;
    const char* name;
    void (*call_back)(struct data_buffer*);
};

struct behaviour behaviour_create_empty(const char*);

void behaviour_add_bind(struct behaviour*, struct key_bind);
