#include <stdio.h>
#include "input.h"

extern Bitboard_t* from_fen(char* fen) {
    Bitboard_t* returning = malloc(sizeof(Bitboard_t));
    int position = 0;
    int phase = 0;
    for(char* c = fen; *c != '\0'; c++) {
        if(phase == 0) {
            const unsigned long placing = (unsigned long) 1 << (63 - position);
            switch(*c) {
                case ' ':
                    ++phase;
                    break;
                case '/':
                    --position;
                    break;
                case '2':
                    ++position;
                    break;
                case '3':
                    position += 2;
                case '4':
                    position += 3;
                    break;
                case '5':
                    position += 4;
                    break;
                case '6':
                    position += 5;
                    break;
                case '7':
                    position += 6;
                    break;
                case '8':
                    position += 7;
                    break;

                case 'p':
                    returning->b_pawns |= placing;
                    break;
                case 'r':
                    returning->b_rooks |= placing;
                    break;
                case 'n':
                    returning->b_knights |= placing;
                    break;
                case 'b':
                    returning->b_bishops |= placing;
                    break;
                case 'q':
                    returning->b_queens |= placing;
                    break;
                case 'k':
                    returning->b_king |= placing;
                    break;
                case 'P':
                    returning->w_pawns |= placing;
                    break;
                case 'R':
                    returning->w_rooks |= placing;
                    break;
                case 'N':
                    returning->w_knights |= placing;
                    break;
                case 'B':
                    returning->w_bishops |= placing;
                    break;
                case 'Q':
                    returning->w_queens |= placing;
                    break;
                case 'K':
                    returning->w_king |= placing;
                    break;
            }

            ++position;
        }
        else if(phase == 1) {
            switch(*c) {
                case 'w':
                    returning-> flags |= (unsigned long) 1;
                    break;
                case 'b':
                    returning-> flags |= (unsigned long) 0;
                    break;
                case ' ':
                    ++phase;
                    break;
            }
        }
        else if(phase == 2) {
            switch(*c) {
                case 'K':
                    returning-> flags |= (unsigned long) 1 << 1;
                    break;
                case 'Q':
                    returning-> flags |= (unsigned long) 1 << 2;
                    break;
                case 'k':
                    returning-> flags |= (unsigned long) 1 << 3;
                    break;
                case 'q':
                    returning-> flags |= (unsigned long) 1 << 4;
                    break;
                case ' ':
                    ++phase;
                    break;
            }
        }
    }

    calc_figures(returning);

    return returning;
}

extern Bitboard_t* from_standard_fen() {
    return from_fen(NORMAL_POS_FEN);
}
