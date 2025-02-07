#pragma once

struct key_bind {
    int bind[8];
    unsigned char size;

    void (*func)(const struct key_bind*);
};

unsigned char input_process(const int*, unsigned char);
