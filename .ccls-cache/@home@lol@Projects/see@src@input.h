#pragma once

#include <stddef.h>

struct key_bind {
    int bind[8];
    unsigned char size;
    const char* argument;

    void (*func)(const char*);
};

struct mode {
    unsigned char name;
    struct key_bind binds[];
};

unsigned char input_process(const int*, unsigned char);
