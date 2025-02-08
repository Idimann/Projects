#include "lexer.h"
#include "parser.h"

//Ik this is a dumb way to do this
//gcc -o release main.c lexer.c parser.c collector.c

int main(int argc, char** argv) {
    char* testing = "";

    const Token_List_t tokens = lexer_lex(testing);

    Block_List_t blocks = parser_from_tokens(tokens);
    parser_collect_brackets(&blocks);
    parser_collect_breaks(&blocks);

    parser_print(&blocks, 0);

    return 0;
}
