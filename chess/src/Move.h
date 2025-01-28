#include <stdlib.h>
#include "bitboards.h"

#pragma once

// A move needs 16 bits to be stored
// bit  0 - 5: destination square (from 0 to 63)
// bit  6 - 11: origin square (from 0 to 63)
// bit 12 - 13: promotion piece type (from KNIGHT 0 to QUEEN 4)
// bit 14 - 15: special move flag: promotion (1), en passant (2), castling (3)
typedef ushort Move_t;

typedef enum {
    WEST = -1,
    EAST = 1,
    NORTH = 8,
    SOUTH = -8,
    NORTH_WEST = 7,
    NORTH_EAST = 9,
    SOUTH_EAST = -7,
    SOUTH_WEST = -9,
} Directions_e;

extern ulong get_dest_mask(Move_t input);
extern ulong get_origin_mask(Move_t input);
extern unsigned char get_promotion_piece(Move_t input);
