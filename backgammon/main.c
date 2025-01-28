#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    uint32_t fields[3];
    uint8_t outside;
} game_t;

typedef uint8_t move_t;

static const game_t NORMAL_POS = {
    .fields = {
        //     |   |   |   |   |   |   |   |   |
        [0] = 0b01110000101100000000000000000100,
        [1] = 0b00000000000010111010000000000000,
        [2] = 0b01010000000000000000101000000110
    },
    .outside = 0
};

static void applyMove(uint32_t* first, uint32_t* second, move_t move) {
    const move_t firstMove = (move & 0b00001111) * 4;
    const move_t secondMove = ((move & 0b11110000) >> 4) * 4;

    *first = (~(0b1110 << firstMove) & *first) |
        (((((0b1110 << firstMove) & *first) >> (firstMove + 1)) - 1) << (firstMove + 1));

    if(*second & (0b1110 << secondMove) && *second & (0b0001 << secondMove)) {
    }
}

static uint8_t getNum(uint32_t* num, uint8_t index) {
    return (*num & (0b1110 << (index * 4))) >> (index * 4 + 1);
}

static uint8_t getOwner(uint32_t* num, uint8_t index) {
    if(getNum(num, index) == 0)
        return '-';

    return ((*num & (0b0001 << (index * 4))) >> (index * 4)) ? 'X' : 'O';
}

static void display(game_t* game) {
    printf(" _______________________________________________\n");
    printf("|%i|%i|%i|%i|%i|%i|%i|%i|%i|%i|%i|%i|%i|%i|%i|%i|%i|%i|%i|%i|%i|%i|%i|%i|\n",
            getNum(&game->fields[0], 0),
            getNum(&game->fields[0], 1),
            getNum(&game->fields[0], 2),
            getNum(&game->fields[0], 3),
            getNum(&game->fields[0], 4),
            getNum(&game->fields[0], 5),
            getNum(&game->fields[0], 6),
            getNum(&game->fields[0], 7),

            getNum(&game->fields[1], 0),
            getNum(&game->fields[1], 1),
            getNum(&game->fields[1], 2),
            getNum(&game->fields[1], 3),
            getNum(&game->fields[1], 4),
            getNum(&game->fields[1], 5),
            getNum(&game->fields[1], 6),
            getNum(&game->fields[1], 7),

            getNum(&game->fields[2], 0),
            getNum(&game->fields[2], 1),
            getNum(&game->fields[2], 2),
            getNum(&game->fields[2], 3),
            getNum(&game->fields[2], 4),
            getNum(&game->fields[2], 5),
            getNum(&game->fields[2], 6),
            getNum(&game->fields[2], 7));

    printf("|%c|%c|%c|%c|%c|%c|%c|%c|%c|%c|%c|%c|%c|%c|%c|%c|%c|%c|%c|%c|%c|%c|%c|%c|\n",
            getOwner(&game->fields[0], 0),
            getOwner(&game->fields[0], 1),
            getOwner(&game->fields[0], 2),
            getOwner(&game->fields[0], 3),
            getOwner(&game->fields[0], 4),
            getOwner(&game->fields[0], 5),
            getOwner(&game->fields[0], 6),
            getOwner(&game->fields[0], 7),

            getOwner(&game->fields[1], 0),
            getOwner(&game->fields[1], 1),
            getOwner(&game->fields[1], 2),
            getOwner(&game->fields[1], 3),
            getOwner(&game->fields[1], 4),
            getOwner(&game->fields[1], 5),
            getOwner(&game->fields[1], 6),
            getOwner(&game->fields[1], 7),

            getOwner(&game->fields[2], 0),
            getOwner(&game->fields[2], 1),
            getOwner(&game->fields[2], 2),
            getOwner(&game->fields[2], 3),
            getOwner(&game->fields[2], 4),
            getOwner(&game->fields[2], 5),
            getOwner(&game->fields[2], 6),
            getOwner(&game->fields[2], 7));

    printf(" _______________________________________________\n");
}

int main(int argc, char** argv) {
    game_t* game = malloc(sizeof(game_t));
    game->fields[0] = NORMAL_POS.fields[0];
    game->fields[1] = NORMAL_POS.fields[1];
    game->fields[2] = NORMAL_POS.fields[2];
    game->outside = NORMAL_POS.outside;

    display(game);

    applyMove(&game->fields[0], &game->fields[0], 0b00100000);

    display(game);

    return 0;
}
