#include "bitboards.h"

#pragma once

#define NORMAL_POS_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

extern Bitboard_t* from_fen(char* fen);
extern Bitboard_t* from_standard_fen();
