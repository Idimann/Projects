#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char array[30000] = {0};
unsigned long position = 0;

void doInterpret(char* buffer) {
    char* newReading;
    unsigned long newSize = 0;

    for(char* c = buffer; *c != '\0'; c++) {
        switch(*c) {
            case '[':
                for(char* d = c + 1; *d != '\0' && *d != ']'; d++)
                    ++newSize;

                newReading = malloc(sizeof(char) * newSize);
                newSize = 0;

                for(char* d = c + 1; *d != '\0' && *d != ']'; d++) {
                    newReading[newSize] = *d;
                    ++newSize;
                }

                break;
            case ']':
                while(array[position])
                    doInterpret(newReading);
                break;
            case ',':
                scanf(" %c", &(array[position]));
                break;
            case '>':
                ++position;
                break;
            case '<':
                --position;
                break;
            case '.':
                printf("%c", array[position]);
                break;
            case '+':
                ++array[position];

                array[position] = array[position] % 256;
                break;
            case '-':
                --array[position];

                if(array[position] < 0)
                    array[position] = 255;
                break;
        }
    }
}

int main(int argc, char* argv[]) {
    if(argc < 2) {
        printf("No file provided!\n");
        return 1;
    }

    FILE* file = fopen(argv[1], "r");

    if(file == NULL) {
        printf("File doesnt exists!\n");
        free(file);
        return 1;
    }

    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    while((read = getline(&line, &len, file)) != -1) {
        doInterpret(line);
    }

    printf("\n");

    return 0;
}
