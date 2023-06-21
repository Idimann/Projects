#include <stdio.h>
#include <stdlib.h>

int doScore(char first, char second) {
    switch(first) {
        case 'A':
            switch(second) {
                case 'X':
                    return 4;
                case 'Y':
                    return 8;
                case 'Z':
                    return 3;
            }
        case 'B':
            switch(second) {
                case 'X':
                    return 1;
                case 'Y':
                    return 5;
                case 'Z':
                    return 9;
            }
        case 'C':
            switch(second) {
                case 'X':
                    return 7;
                case 'Y':
                    return 2;
                case 'Z':
                    return 6;
            }
    }

    return 0;
}

int main(int argc, char* argv[]) {

    char* input = "A YB XC Z";

    char prev = 0;

    int score = 0;

    for(char* c = input; *c != '\0'; c++) {
        if(*c == ' ')
            continue;

        if(prev == 0)
            prev = *c;
        else {
            score += doScore(prev, *c);
            //printf("[%c %c %i] ", prev, *c, doScore(prev, *c));
            prev = 0;
        }
    }

    printf("%i\n", score);

    return 0;
}
