#include "bitboards.h"

extern ulong calc_figures(Bitboard_t* input) {
    input->w_figures = input->w_king | input->w_pawns | input->w_rooks | input->w_queens | input->w_bishops | input->w_knights;
    input->b_figures = input->b_king | input->b_pawns | input->b_rooks | input->b_queens | input->b_bishops | input->b_knights;

    if(input->flags & (unsigned long) 1)
        return input->w_figures;

    return input->b_figures;
}

extern ulong calc_pawn_moves(Bitboard_t *input) {
    return input->w_pawns << 8;
}
