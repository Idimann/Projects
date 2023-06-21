#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void doExpr(FILE* input) {
    char* out = malloc(1);

    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    while ((read = getline(&line, &len, input)) != -1) {
        unsigned long long prevLen = strlen(out);

        out = malloc(sizeof(char) * (strlen(line) + prevLen + 1));

        for(int i = 0; i < strlen(line) + 1; i++)
            out[i + prevLen] = i == strlen(line) ? '\n' : line[i]; 
    }

    printf("%s", out);
}

int main(int agc, char* argv[]) {
    char* input = malloc(sizeof(char) * 20); 
    scanf(" %s", input);

    FILE* file = fopen(input, "w+");

    free(input);
    
    if(file == NULL)
        printf("File not found!\n");

    char mode;
    scanf(" %c", &mode);

    switch(mode) {
        case 'e':
            doExpr(file);
            break;
    }
    
    free(file);
    return 0;
}
