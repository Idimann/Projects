#include "bitboards.h"

#pragma once

//Prints the board in a kinda pretty way into the console
extern void print_board(Bitboard_t* board);

//Ugly code only needed for debug purposes to print out 
//the flags of a bitboard like its a fen string
extern void print_flags(Bitboard_t* board);

//Prints one very simple ulong in the format of a bitboard
extern void print_ulong(ulong input);
