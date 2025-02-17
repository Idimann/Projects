#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#define MAP_SIZE_MAIN 12
#define MAP_SIZE_ADD 3

//12 for the numbers and the last three for the owner
#define MAP_SIZE (MAP_SIZE_MAIN + MAP_SIZE_ADD)

typedef uint8_t map[MAP_SIZE];

void set_map_byte(map map, uint8_t application) {
    const uint8_t pos = ((application >> 4) & 0x0F) / 2;

    if(pos > MAP_SIZE_MAIN)
        return;

    const uint8_t setting = (application) & 0x0F;

    const uint8_t set = map[pos] & ((((application >> 4) & 0x0F) % 2) ? 0x0F : 0xF0);
    map[pos] = set | (setting << ((((application >> 4) & 0x0F) % 2) ? 4 : 0));
}

void set_map_col(map map, uint8_t col, uint8_t pos) {
    if(pos / 8 > MAP_SIZE_ADD)
        return;

    const uint8_t set = (!!col) << (pos % 8);

    map[pos / 8] &= ~set;
    map[pos / 8] |= set;
}

/*
 * 0 <= pos <= 15 &&
 * 0 <= setting <= 15
*/
uint8_t construct_map_application(uint8_t pos, uint8_t setting) {
    return ((pos & 0x0F) << 4) | (setting & 0x0F);
}

uint8_t get_map_num(map map, uint8_t pos) {
    return (map[pos / 2] >> ((pos % 2) ? 4 : 0)) & 0x0F;
}

uint8_t get_map_col(map map, uint8_t pos) {
    return (map[MAP_SIZE_MAIN + pos / 8] >> (pos % 8)) & 0x01;
}

void print_map(map map) {
    for(uint8_t i = 0; i < MAP_SIZE_MAIN; i++)
        printf("|%u", get_map_col(map, i));
    printf("|\n");
    for(uint8_t i = 0; i < MAP_SIZE_MAIN; i++)
        printf("|%u", get_map_num(map, i));

    printf("|\n\n");
    for(uint8_t i = MAP_SIZE_MAIN; i < MAP_SIZE_MAIN * 2; i++)
        printf("|%u", get_map_num(map, i));
    printf("|\n");
    for(uint8_t i = MAP_SIZE_MAIN; i < MAP_SIZE_MAIN * 2; i++)
        printf("|%u", get_map_col(map, i));
    printf("|\n\n");
}

typedef struct {
    map map;
    uint8_t outside;
} game_state;

game_state construct_start_state() {
    return (game_state) {
        .map = {
            0x5, 0, 0x3, 0x5, 0, 0x20, 0x02, 0, 0x50, 0x30, 0, 0x50,
            0b01010000, 0b00010000, 0b10000000
        },
        .outside = 0
    };
}

/*
 * 0x0 - 0x5 => From
 * 0x5 - 0x8 => Number
*/
typedef uint8_t game_move;

game_move construct_move(uint8_t from, uint8_t num) {
    return (from & 0x5) | ((num & 0x3) << 5);
}

void apply_move(game_state state, game_move move) {
    const uint8_t from = move & 0x5;
    const uint8_t from_col = get_map_col(state.map, from);

    const uint8_t to = from + (from_col ? -1 : 1) * ((move >> 5) & 0x3);

    const uint8_t from_num = get_map_num(state.map, from);
    const uint8_t to_num = get_map_num(state.map, to);

    if(!from_num)
        return;

    const uint8_t to_col = get_map_col(state.map, to);

    if(from_col != to_col && to_num > 1)
        return;

    set_map_byte(state.map, construct_map_application(from, from_num - 1));
    set_map_byte(state.map, construct_map_application(to, to_num +
                (from_col == to_col ? 1 : 0)));
}

typedef struct {
    game_move* moves;
    size_t moves_size;
} move_list;

move_list create_pseudo_moves(game_state* gs, unsigned char who, unsigned char num) {
    move_list returning = (move_list) {
        .moves = NULL,
        .moves_size = 0,
    };

    for(size_t i = 0; i < MAP_SIZE_MAIN * 2; i++) {
        if(who ? (i < num) : (i >= MAP_SIZE_MAIN * 2 - num))
            continue;

        if(get_map_col(gs->map, i) == who)
            ++returning.moves_size;
    }

    returning.moves = malloc(sizeof(game_move) * returning.moves_size);

    size_t index = 0;
    for(size_t i = 0; i < MAP_SIZE_MAIN * 2; i++) {
        if(who ? (i < num) : (i >= MAP_SIZE_MAIN * 2 - num))
            continue;

        if(get_map_col(gs->map, i) == who) {
            returning.moves[index] = construct_move(i, num);
            printf("%lu, %u\n", i, num);

            ++index;
        }
    }

    return returning;
}

int main(int argc, char** argv) {
    game_state gs = construct_start_state();
    print_map(gs.map);

    move_list moves = create_pseudo_moves(&gs, 0, 3);

    /*for(size_t i = 0; i < moves.moves_size; i++) {*/
    /*    unsigned char data = moves.moves[i];*/
    /**/
    /*    printf("From: %u Num: %u\n", data & 0b00011111, data & 0b11100000);*/
    /*}*/

    return 0;
}
