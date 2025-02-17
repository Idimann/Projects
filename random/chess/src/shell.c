#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern void shell_run() {
    char* input = malloc(sizeof(char) * 1024);

    do {
        scanf(" %s", input);



    } while(strcmp("exit", input));
}
