#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int field[7][6] = {0};

void printField() {
    printf("1 2 3 4 5 6 7\n");

    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 7; j++) {
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

int getMax(const int pos) {
    for(int i = 5; i >= 0; i--) {
        if(field[pos][i] == 0)
            return i;
    }

    return -1;
}

int hasWonShort() {
    for(int i = 0; i < 7; i++) {
        for(int j = 0; j < 6; j++) {
            if(field[i][j] == 2 && 
                    field[i][j] == field[i + 1][j] && 
                    field[i][j] == field[i + 2][j])
                return 1;

            if(field[i][j] == 2 && 
                    field[i][j] == field[i][j + 1] && 
                    field[i][j] == field[i][j + 2])
                return 1;
            
            if(field[i][j] == 2 && 
                    field[i][j] == field[i + 1][j + 1] && 
                    field[i][j] == field[i + 2][j + 2])
                return 1;

            if(field[i][j] == 2 && 
                    field[i][j] == field[i + 1][j - 1] && 
                    field[i][j] == field[i + 2][j - 2])
                return 1;
        }
    }
    
    return 0;
}

int hasWon() {
    int isTie = 1;

    for(int i = 0; i < 7; i++) {
        for(int j = 0; j < 6; j++) {
            if(field[i][j] == 0)
                isTie = 0;

            if(field[i][j] != 0 && 
                    field[i][j] == field[i + 1][j] && 
                    field[i][j] == field[i + 2][j] && 
                    field[i][j] == field[i + 3][j])
                return field[i][j];

            if(field[i][j] != 0 && 
                    field[i][j] == field[i][j + 1] && 
                    field[i][j] == field[i][j + 2] && 
                    field[i][j] == field[i][j + 3])
                return field[i][j];
            if(field[i][j] != 0 && 
            
                    field[i][j] == field[i + 1][j + 1] && 
                    field[i][j] == field[i + 2][j + 2] && 
                    field[i][j] == field[i + 3][j + 3])
                return field[i][j];

            if(field[i][j] != 0 && 
                    field[i][j] == field[i + 1][j - 1] && 
                    field[i][j] == field[i + 2][j - 2] && 
                    field[i][j] == field[i + 3][j - 3])
                return field[i][j];
        }
    }

    if(isTie)
        return -1;
    
    return 0;
}

int walkTree(const int moves) {
    switch(hasWon()) {
        case -1:
            return 0;
        case 1:
            return -1;
        case 2:
            return 1;
    }

    if(moves == 9)
        return hasWonShort();

    int value = (moves % 2 == 0 ? -1 : 1);

    int prevArr[7][6];
    memcpy(prevArr, field, sizeof(field));

    for(int i = 0; i < 7; i++) {
        int max = getMax(i);

        if(field[i][max] == 0) {
            field[i][max] = (moves % 2 == 0 ? 2 : 1);
            const int nValue = walkTree(moves + 1);


            if((moves % 2 == 0 && nValue > value) || (moves % 2 != 0 && nValue < value)) {
                value = nValue;
                if(nValue != 0) {
                    memcpy(field, prevArr, sizeof(field));
                    break;
                }
            }

            memcpy(field, prevArr, sizeof(field));
        }
    }

    return value;
}

int* genMove() {
    int* returning = malloc(sizeof(int) * 2);
    int value = -1;

    int prevArr[7][6];
    memcpy(prevArr, field, sizeof(field));

    for(int i = 0; i < 7; i++) {
        int max = getMax(i);

        if(field[i][max] == 0) {
            field[i][max] = 2;
            const int nValue = walkTree(1);

            if(nValue > value) {
                value = nValue;
                returning[0] = i;
                returning[1] = max;

                if(nValue != 0) {
                    memcpy(field, prevArr, sizeof(field));
                    break;
                }
            }

            memcpy(field, prevArr, sizeof(field));
        }
    }

    return returning;
}

int* userInput() {
    int* returning = malloc(sizeof(int) * 2);

    scanf("%i", &(returning[1]));

    --returning[1];

    returning[0] = getMax(returning[1]);

    return returning;
}

int main(int argc, char* argv[]) {
    int who = 0;

    printField();

    do {
        if(!who) {
            int* input = userInput();
            while(input[0] > 5 || input[1] > 6 || field[input[1]][input[0]] != 0)
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
