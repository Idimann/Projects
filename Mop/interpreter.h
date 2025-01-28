#pragma once

#include "parser.h"

typedef enum {
    PRIMTIVE,
    SET,
    TUPLE,
    FUNCTION
} Object_Type;

typedef struct {
    Object_Type type;
    void* def; //This is either the primitive counter, an array with all tuple elements or a
               //pointer to a function/set def
} Object;

typedef enum {
    FINITE,
    INFINITE
} Set_Type;

typedef struct {
    Set_Type type;
    void* check; //This is either an array if its finite or a function pointer to a c function
                 //that returns wether something is in the set or not
} Set_Definition;

typedef struct {
    Set_Definition inputSet;
    Set_Definition outputSet;
} Func_Definition;

typedef struct {
    Object* stack;
    size_t size;
    size_t pos;
    size_t contextPos;
} Object_Stack;

void interpreter_do(Block_List_t* input);
