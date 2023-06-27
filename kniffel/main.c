#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum Types_e {
    NUMBERS,
    THREE_PASH,
    FOUR_PASH,
    FULL_HOUSE,
    SMALL_STREET,
    BIG_STREET,
    KNIFFEL,
    CHANCE
};

struct Combi_t {
    int value;
    char* name;
};

struct Ding_t {
    int value;
    enum Types_e type;
    int done;
};

typedef struct Ding_t Field;

Field TODO_LIST[] = {
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

Field* createArray() {
    Field* returning = malloc(sizeof(TODO_LIST));
    memcpy(returning, TODO_LIST, sizeof(TODO_LIST));

    return returning;
}

int calcMissingToBonus(Field* array) {
    int returning = 0;

    for(int i = 0; i < 6; i++) {
        if(array[i].done != 0)
            returning += (i + 1) * 3 - (0 > array[i].done ? 0 : array[i].done);
    }

    return returning;
}

int calcScore(Field* array) {
    int returning = 0;

    for(int i = 0; i < 6; i++)
        returning += (array[i].done > 0 ? array[i].done : 0);

    if(returning >= 63)
        returning += 35;

    for(int i = 6; i < 13; i++)
        returning += (array[i].done > 0 ? array[i].done : 0);

    return returning;
}

int canDo(const int index, int throwing[]) {
    int returning = 0;

    int pashes[6] = {0};
    int donePash = 0;

    int doneHouse = 2;
    int smallStreet = 0;
    int advancing = 0;

    int quit = 0;

    switch(TODO_LIST[index].type) {
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
                returning = TODO_LIST[index].value;

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
                returning = TODO_LIST[index].value;

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
                returning = TODO_LIST[index].value;

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
                returning = TODO_LIST[index].value;

            break;
        case CHANCE:
            for(int i = 0; i < 5; i++)
                returning += throwing[i];
            break;
    }

    return returning;
}

void printEnum(const int nNumber, const int number, Field thing, const int value, const int calc) {
    printf("%i.\t", nNumber);

    switch(thing.type) {
        case NUMBERS:
            switch(number) {
                case 1:
                    printf("Einser\t\t(%i | %i | %i)\n", value, value - 3, -calc + (value - 3));
                    break;
                case 2:
                    printf("Zweier\t\t(%i | %i | %i)\n", value, value - 6, -calc + (value - 6));
                    break;
                case 3:
                    printf("Dreier\t\t(%i | %i | %i)\n", value, value - 9, -calc + (value - 9));
                    break;
                case 4:
                    printf("Vierer\t\t(%i | %i | %i)\n", value, value - 12, -calc + (value - 12));
                    break;
                case 5:
                    printf("Fuenfer\t\t(%i | %i | %i)\n", value, value - 15, -calc + (value - 15));
                    break;
                case 6:
                    printf("Sechser\t\t(%i | %i | %i)\n", value, value - 18, -calc + (value - 18));
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
    }
}

int main(int argc, char* argv[]) {
    int iterating = 1;

    int throwing[5] = {0};

    Field* players[argc - 1];

    for(int i = 0; i < argc - 1; i++)
        players[i] = createArray();

    for(int i = 0; i < 13; i++) {
        for(int j = 1; j < argc; j++) {
            printf("%s du bist dran!\n", argv[j]);
            
            const int missing = calcMissingToBonus(players[j - 1]);
            
            if(missing < 0)
                printf("Du hast extra %i fuer den Bonus\n", -missing);
            else if(missing > 0)
                printf("Dir fehlen %i fuer den Bonus\n", missing);
            
            printf("Deine Optionen:\n\n");

            for(int k = 0; k < 13; k++) {
                if(players[j - 1][k].done == 0)
                    printEnumSimple(k + 1, players[j - 1][k]);
            }

            printf("\n");
            scanf(" %i %i %i %i %i", &throwing[0], &throwing[1], &throwing[2], &throwing[3], &throwing[4]);

            printf("\n0.\tEtwas streichen\n");
            int iterating = 1;
            for(int k = 0; k < 13; k++) {
                if(players[j - 1][k].done == 0 && canDo(k, throwing)) {
                    printEnum(iterating, k + 1, players[j - 1][k], canDo(k, throwing), calcMissingToBonus(players[j - 1]));
                    ++iterating;
                }
            }
            printf("\n");

            int input;
            scanf(" %i", &input);

            iterating = 1;

            if(input == 0) {
                printf("\n");
                for(int k = 0; k < 13; k++) {
                    if(players[j - 1][k].done == 0) {
                        printf("%i.", iterating);
                        printEnumSimple(k + 1, players[j - 1][k]);
                        ++iterating;
                    }
                }
                printf("\n");

                scanf(" %i", &input);

                iterating = 1;

                for(int k = 0; k < 13; k++) {
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
                for(int k = 0; k < 13; k++) {
                    if(players[j - 1][k].done == 0 && canDo(k, throwing)) {
                        if(iterating == input) {
                            players[j - 1][k].done = canDo(k, throwing);
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
