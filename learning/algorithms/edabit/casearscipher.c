#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    char input[1024];
    scanf(" %s", input);

    int offset;
    scanf(" %i", &offset);

    char mode;
    scanf(" %c", &mode);

    for(char* c = input; *c != '\0'; c++) {
        unsigned isLower = *c <= 'z' && *c >= 'a';

        if(!isLower && (*c < 'A' || *c > 'Z'))
            continue;

        unsigned long long character = (unsigned long long) *c;

        switch(mode) {
            case 'E':
            case 'e':
                character += offset;

                if((isLower && character > 'z') || (!isLower && character > 'Z'))
                    character = character % (isLower ? 'z' : 'Z') + (isLower ? 'a' : 'A') - 1;

                *c = (char) character;
                break;
            case 'D':
            case 'd':
                character -= offset;

                if((isLower && character < 'a') || (!isLower && character < 'A'))
                    character = (isLower ? 'z' : 'Z') - ((isLower ? 'a' : 'A') - character) + 1;

                *c = (char) character;
                break;
        }
    }

    printf("%s\n", input);

    return 0;
}
