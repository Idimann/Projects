#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    char* input;
    scanf(" %s", input);

    unsigned long strlen = 0;

    for(char* c = input; *c != '\0'; c++)
        ++strlen;

    for(int i = 0; i < strlen / 2; i++) {
        char original = input[i];
        
        input[i] = input[strlen - i - 1];
        input[strlen - i - 1] = original;
    }

    printf("%s\n", input);

    return 0;
}
