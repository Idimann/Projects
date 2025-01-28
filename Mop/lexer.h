#pragma once
#include <stdio.h>

typedef enum {
    INVALID,
    BREAK,
    LBRACKET,
    RBRACKET,
    LCURLY,
    RCURLY,
    LCORNER,
    RCORNER,
    COMMA,
    BAR,
    HASHTAG,
    ARROW,
    CONDITION_ARROW,
    DEFINE,
    DECLARE,
    KEY_FROM,
    KEY_WITH,
    KEY_MODULE,
    NAME
} Token_Type;

typedef struct {
    Token_Type type;
    const char* string;
    size_t size;
} Token_t;

typedef struct {
    Token_t* list;
    size_t size;
} Token_List_t;

Token_List_t lexer_lex(char* data);
void lexer_print(const Token_List_t list);
