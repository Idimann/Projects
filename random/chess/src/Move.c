#include "Move.h"

extern ulong get_dest_mask(Move_t input) {
    return (unsigned long) 1 << (input & (((unsigned long) 1 << 6) - 1));
}

extern ulong get_origin_mask(Move_t input) {
    return (unsigned long) 1 << (input & ((((unsigned long) 1 << 11) - 1) << 6));
}

extern unsigned char get_promotion_piece(Move_t input) {
    return (unsigned long) 1 << (input & ((((unsigned long) 1 << 13) - 1) << 12));
}
