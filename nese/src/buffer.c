#include "buffer.h"
#include "run.h"

#include <stdio.h>
#include <string.h>

static enum ErrType write_to_file(struct buffer* input) {
    FILE* f = fopen(input->callback_addr, "w");

    if(!f)
        return ERR_FILE;

    fwrite(input->text, input->size, sizeof(char), f);
    fclose(f);

    return ERR_NONE;
}

static enum ErrType read_from_file(struct buffer* input) {
    FILE* f = fopen(input->callback_addr, "r");

    if(!f)
        return ERR_FILE;


    if(input->size && input->text)
        buffer_clear_text(input);

    fseek(f, 0L, SEEK_END);
    input->size = ftell(f);
    rewind(f);

    if(input->size) {
        input->text = malloc(sizeof(char) * input->size);

        fread(input->text, sizeof(char), input->size, f);
    }

    fclose(f);
    return ERR_NONE;
}

struct buffer buffer_create_empty() {
    return (struct buffer) {
        .text = NULL,
        .size = 0,
        .write_func = NULL,
        .load_func = NULL,
        .callback_addr = NULL
    };
}

enum ErrType buffer_clear_text(struct buffer* input) {
    if(!input->size || !input->text)
        return ERR_IMPOSSIBLE;

    free(input->text);
    input->text = NULL;
    input->size = 0;
    return ERR_NONE;
}

enum ErrType buffer_clear_callback(struct buffer* input) {
    if(!input->callback_addr)
        return ERR_IMPOSSIBLE;

    free(input->callback_addr);
    input->callback_addr = NULL;
    return ERR_NONE;
}

enum ErrType buffer_write(struct buffer* input) {
    if(!input->write_func)
        return ERR_IMPOSSIBLE;

    input->write_func(input);
    return ERR_NONE;
}

enum ErrType buffer_load(struct buffer* input) {
    if(!input->load_func)
        return ERR_IMPOSSIBLE;

    input->load_func(input);
    return ERR_NONE;
}

enum ErrType buffer_setup_file(struct buffer* input, const char* file) {
    buffer_attach_callback_to_file(input, file);
    buffer_attach_write_to_file(input);
    buffer_attach_load_to_file(input);

    return input->load_func(input);
}

void buffer_attach_callback_to_file(struct buffer* input, const char* file) {
    if(input->callback_addr)
        buffer_clear_callback(input);

    input->callback_addr = malloc(sizeof(char) * (strlen(file) + 1));
    strcpy(input->callback_addr, file);
}

void buffer_attach_write_to_file(struct buffer* input) {
    input->write_func = write_to_file;
}

void buffer_attach_load_to_file(struct buffer* input) {
    input->load_func = read_from_file;
}

void buffer_setup_text(struct buffer* input, const char* text) {
    if(input->size && input->text)
        buffer_clear_text(input);

    input->size = sizeof(char) * (strlen(text) + 1);
    input->text = malloc(input->size);
    strcpy(input->text, text);

    input->write_func = NULL;
    input->load_func = NULL;
    input->callback_addr = NULL;
}
