#include <stdio.h>

int diff(int first, int second) {
    return first > second ? first - second : second - first;
}

int main(int argc, char* argv[]) {
    int second;
    char secondC;
    scanf("%c %i", &secondC, &second);

    --second;

    int first = secondC - 97;

    int inputArrary[8][8] = {0};

    int array[8][8];

    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            array[i][j] = 0;

            if(i == first && j == second)
                continue;

            if(i == first || j == second || diff(i, first) == diff(j, second))
                array[i][j] = 1;
        }
    }

    array[first][second] = 2;

    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            printf("%i ", array[i][j]);
        }
        printf("\n");
    }

    return 0;
}
