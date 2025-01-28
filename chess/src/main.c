#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "markings.h"
#include "markings.h"
#include "shell.h"
#include "input.h"
#include "output.h"

int main(int argc, char* argv[]) {
    startup_print();
    //shell_run();
    
    //char* input = malloc(sizeof(char) * 64);
    //scanf(" %63[^\n]", input);
    Bitboard_t* board = from_standard_fen();

    print_board(board);
    print_flags(board);
    print_ulong(board->flags);

    return 0;
}
