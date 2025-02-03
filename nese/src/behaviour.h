#pragma once

#include <stddef.h>

enum key_bind_type {
    SIMPLE,
    MACRO
};

struct key_bind {
    enum key_bind_type type;
    union {
        void (*call_back)();
        const char* macro;
    };
};

struct data_buffer;

struct behaviour {
    struct key_bind* binds;
    const char* name;

    void (*call_back)(struct data_buffer*);
};
