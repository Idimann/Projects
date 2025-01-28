#pragma once

#include "lexer.h"

typedef enum {
    TOKEN,
    COLLECTION,
} Block_Type;

typedef struct Block_List {
    struct Block_List* blocks;
    Token_t token;
    Block_Type type;
    size_t size;
} Block_List_t;

Block_List_t parser_from_tokens(const Token_List_t input);

void parser_collect_brackets(Block_List_t* input);
void parser_collect_breaks(Block_List_t* input);

void parser_print(const Block_List_t* input, const size_t additional);
