#include <stdlib.h>

struct buffer {
    char* text;
    size_t size; //Includes the termination char (Is one more than strlen)
    void (*write_func)(struct buffer*);
    void (*load_func)(struct buffer*);
    char* callback_addr;
};

struct buffer buffer_create_empty();

void buffer_clear_text(struct buffer*);
void buffer_clear_callback(struct buffer*);

void buffer_write(struct buffer*);
void buffer_load(struct buffer*);

void buffer_setup_file(struct buffer*, const char*);
void buffer_attach_callback_to_file(struct buffer*, const char*);
void buffer_attach_write_to_file(struct buffer*);
void buffer_attach_load_to_file(struct buffer*);

void buffer_load_simple_text(struct buffer*, const char*);
