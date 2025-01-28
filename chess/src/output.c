#include "output.h"
#include <stdio.h>
#include <stdlib.h>

extern void print_board(Bitboard_t* board) {
    for(int i = 0; i < 8; i++) {
        printf("%c\t", '8' - i);

        for(int j = 0; j < 8; j++) {
            const int pos = 63 - (i * 8 + j);

            if(board->w_pawns & ((unsigned long) 1 << pos))
                printf("P ");
            else if(board->w_king & ((unsigned long) 1 << pos))
                printf("K ");
            else if(board->w_rooks & ((unsigned long) 1 << pos))
                printf("R ");
            else if(board->w_queens & ((unsigned long) 1 << pos))
                printf("Q ");
            else if(board->w_bishops & ((unsigned long) 1 << pos))
                printf("B ");
            else if(board->w_knights & ((unsigned long) 1 << pos))
                printf("N ");
            else if(board->b_pawns & ((unsigned long) 1 << pos))
                printf("p ");
            else if(board->b_king & ((unsigned long) 1 << pos))
                printf("k ");
            else if(board->b_rooks & ((unsigned long) 1 << pos))
                printf("r ");
            else if(board->b_queens & ((unsigned long) 1 << pos))
                printf("q ");
            else if(board->b_bishops & ((unsigned long) 1 << pos))
                printf("b ");
            else if(board->b_knights & ((unsigned long) 1 << pos))
                printf("n ");
        }

        printf("\n");
    }

    printf(" \ta b c d e f g h\n");
}

extern void print_ulong(ulong input) {
    for(int i = 0; i < 8; i++) {
        printf("%c\t", '8' - i);

        for(int j = 0; j < 8; j++) {
            const int pos = 63 - (i * 8 + j);

            if(input & ((unsigned long) 1 << pos))
                printf("X ");
        }

        printf("\n");
    }

    printf(" \ta b c d e f g h\n");
}

extern void print_flags(Bitboard_t *board) {
    if(board->flags & ((unsigned long) 1))
        printf("w");
    else
        printf("b");

    if(board->flags & ((unsigned long) 1 << 1))
        printf("K");
    if(board->flags & ((unsigned long) 1 << 2))
        printf("Q");
    if(board->flags & ((unsigned long) 1 << 3))
        printf("k");
    if(board->flags & ((unsigned long) 1 << 4))
        printf("q");

    printf("\n");
}
