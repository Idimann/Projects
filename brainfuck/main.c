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
                break;
            case '-':
                --array[position];
                break;
            default:
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
        printf("File doesnt exist!\n");
        free(file);
        return 1;
    }

    char* buffer = 0;
    long length;

    FILE* f = fopen(argv[1], "rb");

    if (f) {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);

        buffer = malloc(length);

        if (buffer)
            fread (buffer, 1, length, f);

        fclose (f);
    }

    if (buffer)
        doInterpret(buffer);

    printf("\n");

    return 0;
}
