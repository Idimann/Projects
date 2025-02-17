#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int length;
    char* string;
} Solution_t;

Solution_t solution(char* input) {
    Solution_t returning;
    unsigned short array[265] = {0};
    int counter = 0;
    char* updating = malloc(sizeof(char) * 1);

    for(int i = 0; i < strlen(input); i++) {
        if(!array[input[i]]) {
            array[input[i]] = 1;
            updating = malloc(sizeof(updating) + sizeof(char));
            updating[sizeof(updating) / sizeof(char) - 1] = input[i];
            ++counter;
            continue;
        }

        memset(array, 0, sizeof(array));

        if(counter > returning.length) {
            returning.length = counter;
            returning.string = updating;
        }

        updating = malloc(sizeof(char) * 1);
        counter = 0;
    }

    return returning;
}

int main(int argc, char* argv[]) {
    printf("%i %s\n", solution("abcabcbb").length, solution("abcabcbb").string);
    return 0;
}
