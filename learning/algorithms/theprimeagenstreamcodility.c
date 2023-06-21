#include <stdio.h>
#include <stdlib.h>

char* solution(char chars[], int ints[]) {
    char* returning = malloc(sizeof(chars));

    returning[0] = chars[0];

    int i = ints[0];
    int iterator = 1;

    while(i != 0) {

        returning[iterator] = chars[i];

        ++iterator;
        i = ints[i];
    }

    return returning;
}

int main(int argc, char* argv[]) {

    int array[] = {};
    int input;

    do {

        scanf(" %i", &input);
        int nArray[sizeof(array) / sizeof(int)];

    } while(input != -1);

    printf("%s\n", solution("cdeo", array));

    return 0;
}
