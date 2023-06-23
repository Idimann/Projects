#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int field[3][3] = {0};

void printField() {
    printf("  1 2 3\n");

    for(int i = 0; i < 3; i++) {
        printf("%c ", i + 'a');

        for(int j = 0; j < 3; j++) {
            char printing;
            switch(field[j][i]) {
                case 0:
                    printing = '-';
                    break;
                case 1:
                    printing = 'x';
                    break;
                case 2:
                    printing = 'o';
                    break;
            }

            printf("%c ", printing);
        }

        printf("\n");
    }
}

int hasWon() {
    int isTie = 1;

    for(int i = 0; i < 3; i++) {
        if(field[i][0] != 0 && field[i][0] == field[i][1] && field[i][0] == field[i][2])
            return field[i][0];

        if(field[0][i] != 0 && field[0][i] == field[1][i] && field[0][i] == field[2][i])
            return field[0][i];

        if(isTie)
            for(int j = 0; j < 3; j++) {
                if(field[i][j] == 0)
                    isTie = 0;
            }
    }

    if(isTie)
        return -1;
    
    if(field[1][1] != 0 && field[1][1] == field[0][0] && field[1][1] == field[2][2])
        return field[1][1];

    if(field[1][1] != 0 && field[1][1] == field[0][2] && field[1][1] == field[2][0])
        return field[1][1];
    
    return 0;
}

int walkTree(const int moves) {
    switch(hasWon()) {
        case -1:
            return 0;
        case 1:
            return -100 + moves;
        case 2:
            return 100 - moves;
    }

    int value = (moves % 2 == 0 ? -50 : 50);

    int prevArr[3][3];
    memcpy(prevArr, field, sizeof(int) * 9);

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(field[i][j] == 0) {
                field[i][j] = (moves % 2 == 0 ? 2 : 1);
                const int nValue = walkTree(moves + 1);

                if((moves % 2 == 0 && nValue > value) || (moves % 2 != 0 && nValue < value))
                    value = nValue;

                memcpy(field, prevArr, sizeof(int) * 9);
            }
        }
    }

    return value;
}

int* genMove() {
    int* returning = malloc(sizeof(int) * 2);
    int value = -50;

    int prevArr[3][3];
    memcpy(prevArr, field, sizeof(field));

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(field[i][j] == 0) {
                field[i][j] = 2;
                const int nValue = walkTree(1);
                
                if(nValue > value) {
                    value = nValue;
                    returning[0] = i;
                    returning[1] = j;
                }

                memcpy(field, prevArr, sizeof(int) * 9);
            }
        }
    }

    return returning;
}

int* userInput() {
    int* returning = malloc(sizeof(int) * 2);

    char input;

    scanf(" %c %i", &input, &(returning[1]));

    returning[0] = input - 'a';
    --returning[1];

    return returning;
}

int main(int argc, char* argv[]) {
    int who = 0;

    do {
        if(who) {
            int* input = userInput();
            while(input[0] > 2 || input[1] > 2 || field[input[1]][input[0]] != 0)
                input = userInput();

            field[input[1]][input[0]] = 1;
        } else {
            int* input = genMove();

            field[input[0]][input[1]] = 2;
        }

        who = !who;
        printField();
    } while(hasWon() == 0);

    if(hasWon() == -1)
        printf("Its a tie!\n");
    else
        printf("Player %i has won!\n", hasWon());

    return 0;
}
