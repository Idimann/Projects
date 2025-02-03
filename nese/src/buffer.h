#pragma once

#include <stdlib.h>

#include "run.h"

struct buffer {
    char* text;
    size_t size; //Includes the termination char (Is one more than strlen)
    enum ErrType (*write_func)(struct buffer*);
    enum ErrType (*load_func)(struct buffer*);
    char* callback_addr;
};

struct buffer buffer_create_empty();

enum ErrType buffer_clear_text(struct buffer*);
enum ErrType buffer_clear_callback(struct buffer*);

enum ErrType buffer_write(struct buffer*);
enum ErrType buffer_load(struct buffer*);

enum ErrType buffer_setup_file(struct buffer*, const char*);
void buffer_attach_callback_to_file(struct buffer*, const char*);
void buffer_attach_write_to_file(struct buffer*);
void buffer_attach_load_to_file(struct buffer*);

void buffer_setup_text(struct buffer*, const char*);
