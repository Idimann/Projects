#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long TYPE_AMOUNT = 13;

enum Types_e {
    //Normal
        NUMBERS,
        THREE_PASH,
        FOUR_PASH,
        FULL_HOUSE,
        SMALL_STREET,
        BIG_STREET,
        KNIFFEL,
        CHANCE,

    //Custom

        //Easy
            MINI_STREET,
            TWO_PAIRS,
            FOUR_EVENS,
            FOUR_UNEVENS,
            KNIFFER,

        //Hard
            ONLY_ONCE,
            EXTREMES,
            MIDDLE_STUFF,
            NON_PRIMES,
};

struct Combi_t {
    int value;
    char* name;
};

typedef struct {
    int value;
    enum Types_e type;
    int done;
} Field;

Field ALL_LIST[] = {
    [0] = {
        .value = 0,
        .type = NUMBERS,
        .done = 0,
    },

    [1] = {
        .value = 0,
        .type = NUMBERS,
        .done = 0,
    },

    [2] = {
        .value = 0,
        .type = NUMBERS,
        .done = 0,
    },

    [3] = {
        .value = 0,
        .type = NUMBERS,
        .done = 0,
    },

    [4] = {
        .value = 0,
        .type = NUMBERS,
        .done = 0,
    },

    [5] = {
        .value = 0,
        .type = NUMBERS,
        .done = 0,
    },

    [6] = {
        .value = 0,
        .type = THREE_PASH,
        .done = 0,
    },

    [7] = {
        .value = 0,
        .type = FOUR_PASH,
        .done = 0,
    },

    [8] = {
        .value = 25,
        .type = FULL_HOUSE,
        .done = 0,
    },

    [9] = {
        .value = 30,
        .type = SMALL_STREET,
        .done = 0,
    },

    [10] = {
        .value = 40,
        .type = BIG_STREET,
        .done = 0,
    },

    [11] = {
        .value = 50,
        .type = KNIFFEL,
        .done = 0,
    },

    [12] = {
        .value = 25,
        .type = MINI_STREET,
        .done = 0
    },

    [13] = {
        .value = 35,
        .type = SMALL_STREET,
        .done = 0,
    },

    [14] = {
        .value = 20,
        .type = TWO_PAIRS,
        .done = 0
    },

    [15] = {
        .value = 25,
        .type = FOUR_EVENS,
        .done = 0
    },

    [16] = {
        .value = 25,
        .type = FOUR_UNEVENS,
        .done = 0
    },

    [17] = {
        .value = 35,
        .type = KNIFFER,
        .done = 0,
    },

    [18] = {
        .value = 38,
        .type = ONLY_ONCE,
        .done = 0
    },

    [19] = {
        .value = 89,
        .type = EXTREMES,
        .done = 0
    },

    [20] = {
        .value = 79,
        .type = MIDDLE_STUFF,
        .done = 0
    },

    [21] = {
        .value = 69,
        .type = NON_PRIMES,
        .done = 0
    },

    [22] = {
        .value = 0,
        .type = CHANCE,
        .done = 0,
    },
};

Field NORMAL_LIST[] = {
    [0] = {
        .value = 0,
        .type = NUMBERS,
        .done = 0,
    },

    [1] = {
        .value = 0,
        .type = NUMBERS,
        .done = 0,
    },

    [2] = {
        .value = 0,
        .type = NUMBERS,
        .done = 0,
    },

    [3] = {
        .value = 0,
        .type = NUMBERS,
        .done = 0,
    },

    [4] = {
        .value = 0,
        .type = NUMBERS,
        .done = 0,
    },

    [5] = {
        .value = 0,
        .type = NUMBERS,
        .done = 0,
    },

    [6] = {
        .value = 0,
        .type = THREE_PASH,
        .done = 0,
    },

    [7] = {
        .value = 0,
        .type = FOUR_PASH,
        .done = 0,
    },

    [8] = {
        .value = 25,
        .type = FULL_HOUSE,
        .done = 0,
    },

    [9] = {
        .value = 30,
        .type = SMALL_STREET,
        .done = 0,
    },

    [10] = {
        .value = 40,
        .type = BIG_STREET,
        .done = 0,
    },

    [11] = {
        .value = 50,
        .type = KNIFFEL,
        .done = 0,
    },

    [12] = {
        .value = 0,
        .type = CHANCE,
        .done = 0,
    },
};

Field EASY_LIST[] = {
    [0] = {
        .value = 0,
        .type = NUMBERS,
        .done = 0,
    },

    [1] = {
        .value = 0,
        .type = NUMBERS,
        .done = 0,
    },

    [2] = {
        .value = 0,
        .type = NUMBERS,
        .done = 0,
    },

    [3] = {
        .value = 0,
        .type = NUMBERS,
        .done = 0,
    },

    [4] = {
        .value = 0,
        .type = NUMBERS,
        .done = 0,
    },

    [5] = {
        .value = 0,
        .type = NUMBERS,
        .done = 0,
    },

    [6] = {
        .value = 0,
        .type = THREE_PASH,
        .done = 0,
    },

    [7] = {
        .value = 0,
        .type = FOUR_PASH,
        .done = 0,
    },

    [8] = {
        .value = 30,
        .type = FULL_HOUSE,
        .done = 0,
    },

    [9] = {
        .value = 25,
        .type = MINI_STREET,
        .done = 0
    },

    [10] = {
        .value = 35,
        .type = SMALL_STREET,
        .done = 0,
    },

    [11] = {
        .value = 20,
        .type = TWO_PAIRS,
        .done = 0
    },

    [12] = {
        .value = 25,
        .type = FOUR_EVENS,
        .done = 0
    },

    [13] = {
        .value = 25,
        .type = FOUR_UNEVENS,
        .done = 0
    },

    [14] = {
        .value = 35,
        .type = KNIFFER,
        .done = 0,
    },

    [15] = {
        .value = 0,
        .type = CHANCE,
        .done = 0,
    },
};

Field HARD_LIST[] = {
    [0] = {
        .value = 0,
        .type = NUMBERS,
        .done = 0,
    },

    [1] = {
        .value = 0,
        .type = NUMBERS,
        .done = 0,
    },

    [2] = {
        .value = 0,
        .type = NUMBERS,
        .done = 0,
    },

    [3] = {
        .value = 0,
        .type = NUMBERS,
        .done = 0,
    },

    [4] = {
        .value = 0,
        .type = NUMBERS,
        .done = 0,
    },

    [5] = {
        .value = 0,
        .type = NUMBERS,
        .done = 0,
    },

    [6] = {
        .value = 0,
        .type = THREE_PASH,
        .done = 0,
    },

    [7] = {
        .value = 0,
        .type = FOUR_PASH,
        .done = 0,
    },

    [8] = {
        .value = 20,
        .type = FULL_HOUSE,
        .done = 0,
    },

    [9] = {
        .value = 35,
        .type = SMALL_STREET,
        .done = 0,
    },

    [10] = {
        .value = 55,
        .type = BIG_STREET,
        .done = 0,
    },

    [11] = {
        .value = 38,
        .type = ONLY_ONCE,
        .done = 0
    },

    [12] = {
        .value = 89,
        .type = EXTREMES,
        .done = 0
    },

    [13] = {
        .value = 79,
        .type = MIDDLE_STUFF,
        .done = 0
    },

    [14] = {
        .value = 69,
        .type = NON_PRIMES,
        .done = 0
    },

    [15] = {
        .value = 99,
        .type = KNIFFEL,
        .done = 0,
    },

    [16] = {
        .value = 0,
        .type = CHANCE,
        .done = 0,
    },
};

Field* createArray(const int mode) {
    if(mode == 0) {
        Field* returning = malloc(sizeof(ALL_LIST));
        memcpy(returning, ALL_LIST, sizeof(ALL_LIST));

        return returning;
    }
    if(mode == 1) {
        Field* returning = malloc(sizeof(NORMAL_LIST));
        memcpy(returning, NORMAL_LIST, sizeof(NORMAL_LIST));

        return returning;
    } else if(mode == 2) {
        Field* returning = malloc(sizeof(EASY_LIST));
        memcpy(returning, EASY_LIST, sizeof(EASY_LIST));

        return returning;
    } else if(mode == 3) {
        Field* returning = malloc(sizeof(HARD_LIST));
        memcpy(returning, HARD_LIST, sizeof(HARD_LIST));

        return returning;
    }

    return NULL;
}

int calcMissingToBonus(Field* array, const int mode) {
    int returning = 0;

    for(int i = 0; i < 6; i++) {
        if(array[i].done != 0)
            returning += (i + 1) * 3 - (0 > array[i].done ? 0 : array[i].done);
    }

    switch(mode) {
        case 0:
        case 1:
            return returning;
        case 2:
            return returning - 10;
        case 3:
            return returning + 8;
    }

    return returning;
}

int calcScore(Field* array) {
    int returning = 0;

    for(int i = 0; i < 6; i++)
        returning += (array[i].done > 0 ? array[i].done : 0);

    if(returning >= 63)
        returning += 35;

    for(int i = 6; i < TYPE_AMOUNT; i++)
        returning += (array[i].done > 0 ? array[i].done : 0);

    return returning;
}

int canDo(const int index, int throwing[], const int mode) {
    int returning = 0;

    int pashes[6] = {0};
    int donePash = 0;

    int doneHouse = 2;
    int smallStreet = 0;
    int advancing = 0;
    int kniffer = -1;

    int quit = 0;

    Field* LIST = createArray(mode);

    switch(LIST[index].type) {
        case NUMBERS:
            for(int i = 0; i < 5; i++) {
                if(throwing[i] == index + 1)
                    returning += index + 1;
            }
            break;
        case THREE_PASH:
            for(int i = 0; i < 5; i++) {
                returning += throwing[i];
                ++pashes[throwing[i] - 1];
            }

            for(int i = 0; i < 6; i++) {
                if(pashes[i] >= 3) {
                    donePash = 1;
                    break;
                }
            }

            if(!donePash)
                returning = 0;

            break;
        case FOUR_PASH:
            for(int i = 0; i < 5; i++) {
                returning += throwing[i];
                ++pashes[throwing[i] - 1];
            }

            for(int i = 0; i < 6; i++) {
                if(pashes[i] >= 4) {
                    donePash = 1;
                    break;
                }
            }

            if(!donePash)
                returning = 0;

            break;
        case FULL_HOUSE:
            for(int i = 0; i < 5; i++)
                ++pashes[throwing[i] - 1];

            for(int i = 0; i < 6; i++) {
                if(pashes[i] == 2 && doneHouse == 2)
                    --doneHouse;
            }

            for(int i = 0; i < 6; i++) {
                if(pashes[i] == 3)
                    --doneHouse;
            }

            if(!doneHouse)
                returning = LIST[index].value;

            break;
        case SMALL_STREET:
            for(int i = 0; i < 5; i++)
                ++pashes[throwing[i] - 1];

            for(int i = 0; i < 6; i++) {
                if(!((pashes[i] == 2 && !smallStreet) || pashes[i] <= 1)) {
                    quit = 1;
                    break;
                }

                if(pashes[i])
                    ++advancing;
                else if(advancing < 4)
                    advancing = 0;

                if(pashes[i] == 2)
                    smallStreet = 1;
            }

            if(!quit && advancing >= 4)
                returning = LIST[index].value;

            break;
        case BIG_STREET:
            for(int i = 0; i < 5; i++)
                ++pashes[throwing[i] - 1];

            for(int i = 0; i < 6; i++) {
                if(pashes[i] > 1) {
                    quit = 1;
                    break;
                }

                if(pashes[i])
                    ++advancing;
                else if(advancing < 5)
                    advancing = 0;
            }

            if(!quit && advancing == 5)
                returning = LIST[index].value;

            break;
        case KNIFFEL:
            for(int i = 0; i < 5; i++)
                ++pashes[throwing[i] - 1];

            for(int i = 0; i < 6; i++) {
                if(pashes[i] == 5) {
                    quit = 1;
                    break;
                }
            }

            if(quit)
                returning = LIST[index].value;

            break;
        case KNIFFER:
            for(int i = 0; i < 5; i++)
                ++pashes[throwing[i] - 1];

            for(int i = 0; i < 6; i++) {
                if(pashes[i] >= 4) {
                    kniffer = i;

                    if(pashes[i] == 5)
                        quit = 1;

                    break;
                }
            }

            for(int i = 0; i < 6; i++) {
                if(((i - kniffer) == 1 || (kniffer - i) == 1) && pashes[i] == 1) {
                    quit = 1;
                    break;
                }
            }

            if(quit && kniffer != -1)
                returning = LIST[index].value;

            break;
        case CHANCE:
            for(int i = 0; i < 5; i++)
                returning += throwing[i];
            break;
        case MINI_STREET:
            for(int i = 0; i < 5; i++)
                ++pashes[throwing[i] - 1];

            for(int i = 0; i < 6; i++) {
                if(pashes[i])
                    ++advancing;
                else if(advancing < 3)
                    advancing = 0;
            }

            if(advancing >= 3)
                returning = LIST[index].value;
            break;
        case TWO_PAIRS:
            for(int i = 0; i < 5; i++)
                ++pashes[throwing[i] - 1];

            for(int i = 0; i < 6; i++) {
                if(pashes[i] >= 2)
                    --doneHouse;
            }

            if(!doneHouse)
                returning = LIST[index].value;

            break;
        case FOUR_EVENS:
            for(int i = 0; i < 5; i++)
                ++pashes[throwing[i] - 1];

            for(int i = 0; i < 6; i++)
                if((i + 1) % 2 != 0 && pashes[i] > 0)
                    quit += pashes[i];

            if(quit < 2)
                returning = LIST[index].value;

            break;
        case FOUR_UNEVENS:
            for(int i = 0; i < 5; i++)
                ++pashes[throwing[i] - 1];

            for(int i = 0; i < 6; i++)
                if((i + 1) % 2 == 0 && pashes[i] > 0)
                    quit += pashes[i];

            if(quit < 2)
                returning = LIST[index].value;

            break;
        case ONLY_ONCE:
            for(int i = 0; i < 5; i++)
                ++pashes[throwing[i] - 1];

            for(int i = 0; i < 6; i++)
                if(pashes[i] > 1)
                    quit = 1;

            if(!quit)
                returning = LIST[index].value;

            break;
        case EXTREMES:
            for(int i = 0; i < 5; i++)
                ++pashes[throwing[i] - 1];

            for(int i = 0; i < 6; i++)
                if(i != 0 && i != 5 && pashes[i] > 0)
                    quit = 1;

            if(!quit)
                returning = LIST[index].value;

            break;
        case MIDDLE_STUFF:
            for(int i = 0; i < 5; i++)
                ++pashes[throwing[i] - 1];

            for(int i = 0; i < 6; i++)
                if((i == 0 || i == 5) && pashes[i] > 0)
                    quit = 1;

            if(!quit)
                returning = LIST[index].value;

            break;
        case NON_PRIMES:
            for(int i = 0; i < 5; i++)
                ++pashes[throwing[i] - 1];

            for(int i = 0; i < 6; i++)
                if((i == 1 || i == 2 || i == 4) && pashes[i] > 0)
                    quit = 1;

            if(!quit)
                returning = LIST[index].value;

            break;
    }

    return returning;
}

void printEnum(const int nNumber, const int number, Field thing, const int value,
        const int calc) {
    printf("%i.\t", nNumber);

    switch(thing.type) {
        case NUMBERS:
            switch(number) {
                case 1:
                    printf("Einser\t\t(%i | %i | %i)\n", value, value - 3,
                            -calc + (value - 3));
                    break;
                case 2:
                    printf("Zweier\t\t(%i | %i | %i)\n", value, value - 6,
                            -calc + (value - 6));
                    break;
                case 3:
                    printf("Dreier\t\t(%i | %i | %i)\n", value, value - 9,
                            -calc + (value - 9));
                    break;
                case 4:
                    printf("Vierer\t\t(%i | %i | %i)\n", value, value - 12,
                            -calc + (value - 12));
                    break;
                case 5:
                    printf("Fuenfer\t\t(%i | %i | %i)\n", value, value - 15,
                            -calc + (value - 15));
                    break;
                case 6:
                    printf("Sechser\t\t(%i | %i | %i)\n", value, value - 18,
                            -calc + (value - 18));
                    break;
            }
            break;
        case THREE_PASH:
            printf("Dreier Pasch\t(%i)\n", value);
            break;
        case FOUR_PASH:
            printf("Vierer Pasch\t(%i)\n", value);
            break;
        case FULL_HOUSE:
            printf("Full House\t(%i)\n", value);
            break;
        case SMALL_STREET:
            printf("Kleine Strasse\t(%i)\n", value);
            break;
        case BIG_STREET:
            printf("Grosse Strasse\t(%i)\n", value);
            break;
        case KNIFFEL:
            printf("Kniffel\t\t(%i)\n", value);
            break;
        case CHANCE:
            printf("Chance\t\t(%i)\n", value);
            break;
        case MINI_STREET:
            printf("Mini Strasse\t(%i)\n", value);
            break;
        case TWO_PAIRS:
            printf("Zwei Paare\t(%i)\n", value);
            break;
        case FOUR_EVENS:
            printf("Vier gerade\t(%i)\n", value);
            break;
        case FOUR_UNEVENS:
            printf("Vier ungerade\t(%i)\n", value);
            break;
        case ONLY_ONCE:
            printf("Einzelne\t(%i)\n", value);
            break;
        case EXTREMES:
            printf("Extreme\t\t(%i)\n", value);
            break;
        case MIDDLE_STUFF:
            printf("Mittlere Wuerfe\t(%i)\n", value);
            break;
        case NON_PRIMES:
            printf("Keine Primzahlen(%i)\n", value);
            break;
        case KNIFFER:
            printf("Kniffer\t\t(%i)\n", value);
            break;
    }
}

void printEnumSimple(const int number, Field thing) {
    printf("\t");

    switch(thing.type) {
        case NUMBERS:
            switch(number) {
                case 1:
                    printf("Einser\n");
                    break;
                case 2:
                    printf("Zweier\n");
                    break;
                case 3:
                    printf("Dreier\n");
                    break;
                case 4:
                    printf("Vierer\n");
                    break;
                case 5:
                    printf("Fuenfer\n");
                    break;
                case 6:
                    printf("Sechser\n");
                    break;
            }
            break;
        case THREE_PASH:
            printf("Dreier Pasch\n");
            break;
        case FOUR_PASH:
            printf("Vierer Pasch\n");
            break;
        case FULL_HOUSE:
            printf("Full House\n");
            break;
        case SMALL_STREET:
            printf("Kleine Strasse\n");
            break;
        case BIG_STREET:
            printf("Grosse Strasse\n");
            break;
        case KNIFFEL:
            printf("Kniffel!!\n");
            break;
        case CHANCE:
            printf("Chance\n");
            break;
        case MINI_STREET:
            printf("Mini Strasse\n");
            break;
        case TWO_PAIRS:
            printf("Zwei Paare\n");
            break;
        case FOUR_EVENS:
            printf("Vier gerade\n");
            break;
        case FOUR_UNEVENS:
            printf("Vier ungerade\n");
            break;
        case ONLY_ONCE:
            printf("Einzelne\n");
            break;
        case EXTREMES:
            printf("Extreme\n");
            break;
        case MIDDLE_STUFF:
            printf("Mittlere Wuerfe\n");
            break;
        case NON_PRIMES:
            printf("Keine Primzahlen\n");
            break;
        case KNIFFER:
            printf("Kniffer\n");
            break;
    }
}

int main(int argc, char* argv[]) {
    int iterating = 1;

    int throwing[5] = {0};
    Field* players[argc - 1];

    int mode;
    printf("Welche Version des Spiels ist erwuenscht?\n\n"
            "0. Alles\n"
            "1. Classic\n"
            "2. Easy\n"
            "3. Hard\n\n");
    scanf(" %i", &mode);

    switch(mode) {
        case 0:
            TYPE_AMOUNT = 23;
            break;
        case 1:
            TYPE_AMOUNT = 13;
            break;
        case 2:
            TYPE_AMOUNT = 16;
            break;
        case 3:
            TYPE_AMOUNT = 17;
            break;
    }

    for(int i = 0; i < argc - 1; i++)
        players[i] = createArray(mode);

    for(int i = 0; i < TYPE_AMOUNT; i++) {
        for(int j = 1; j < argc; j++) {
            for(int i = 0; i < 5; i++)
                throwing[i] = 0;
            printf("%s du bist dran!\n", argv[j]);

            const int missing = calcMissingToBonus(players[j - 1], mode);

            if(missing < 0)
                printf("Du hast extra %i fuer den Bonus\n", -missing);
            else if(missing > 0)
                printf("Dir fehlen %i fuer den Bonus\n", missing);

            printf("Deine Optionen:\n\n");

            for(int k = 0; k < TYPE_AMOUNT; k++) {
                if(players[j - 1][k].done == 0)
                    printEnumSimple(k + 1, players[j - 1][k]);
            }

            printf("\n");
            while(throwing[0] < 1 || throwing[0] > 6 ||
                    throwing[1] < 1 || throwing[1] > 6 ||
                    throwing[2] < 1 || throwing[2] > 6 ||
                    throwing[3] < 1 || throwing[3] > 6 ||
                    throwing[4] < 1 || throwing[4] > 6) {
                scanf(" %i %i %i %i %i", &throwing[0], &throwing[1], &throwing[2],
                        &throwing[3], &throwing[4]);
            }

            printf("\n0.\tEtwas streichen\n");
            int iterating = 1;
            for(int k = 0; k < TYPE_AMOUNT; k++) {
                if(players[j - 1][k].done == 0 && canDo(k, throwing, mode)) {
                    printEnum(iterating, k + 1, players[j - 1][k], canDo(k, throwing, mode),
                            calcMissingToBonus(players[j - 1], mode));
                    ++iterating;
                }
            }
            printf("\n");

            int input = -1;
            while(input < 0 || input > iterating)
                scanf(" %i", &input);

            iterating = 1;

            if(input == 0) {
                printf("\n");
                for(int k = 0; k < TYPE_AMOUNT; k++) {
                    if(players[j - 1][k].done == 0) {
                        printf("%i.", iterating);
                        printEnumSimple(k + 1, players[j - 1][k]);
                        ++iterating;
                    }
                }
                printf("\n");

                while(input < 1 || input > iterating)
                    scanf(" %i", &input);

                iterating = 1;

                for(int k = 0; k < TYPE_AMOUNT; k++) {
                    if(players[j - 1][k].done == 0) {
                        if(input == iterating) {
                            players[j - 1][k].done = -1;
                            break;
                        }
                        ++iterating;
                    }
                }
            }
            else {
                for(int k = 0; k < TYPE_AMOUNT; k++) {
                    if(players[j - 1][k].done == 0 && canDo(k, throwing, mode)) {
                        if(iterating == input) {
                            players[j - 1][k].done = canDo(k, throwing, mode);
                            break;
                        }
                        ++iterating;
                    }
                }
            }
        }
    }

    struct Combi_t* array = malloc(sizeof(struct Combi_t) * (argc - 1));

    for(int i = 1; i < argc; i++) {
        array[i - 1] = (struct Combi_t) {
            .value = calcScore(players[i - 1]),
            .name = argv[i],
        };
    }

    struct Combi_t* switchting = malloc(sizeof(struct Combi_t));

    for(int j = 0; j < argc - 1; j++) {
        for(int i = argc - 2; i > 0 + j; i--) {
            if(array[i].value > array[i - 1].value) {
                memcpy(switchting, &(array[i - 1]), sizeof(struct Combi_t));

                memcpy(&(array[i - 1]), &(array[i]), sizeof(struct Combi_t));
                memcpy(&(array[i]), switchting, sizeof(struct Combi_t));
            }
        }
    }

    printf("\n");
    for(int i = 0; i < argc - 1; i++)
        printf("%i.\t%s mit %i Punkten\n", i + 1, array[i].name, array[i].value);
    printf("\n");

    return 0;
}
