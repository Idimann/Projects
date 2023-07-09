#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char rotor1[] = "DMTWSILRUYQNKFEJCAZBPGXOHV";
char rotor2[] = "HQZGPJTMOBLNCIFDYAWVEUSRKX";
char rotor3[] = "UQNTXSZFMREHDPLKIBVYGJCWOA";

int firstI;
int secondI;
int thirdI;

char* switches;

char getRotorD(const int rotor, const char input) {
    char iterating = 'A';

    for(int i = 0; i < 26; i++) {
        switch(rotor) {
            case 1:
                if(input == rotor1[(i + firstI) % 26]) {
                    ++firstI;
                    return iterating;
                }
                break;
            case 2:
                if(input == rotor2[(i + secondI) % 26]) {
                    ++secondI;
                    return iterating;
                }
                break;
            case 3:
                if(input == rotor3[(i + thirdI) % 26]) {
                    ++thirdI;
                    return iterating;
                }
                break;
        }
        ++iterating;
    }

    return input;
}

char getRotor(const int rotor, const char input) {
    char iterating = 'A';

    for(int i = 0; i < 26; i++) {
        switch(rotor) {
            case 1:
                if(input == iterating) {
                    ++firstI;
                    return rotor1[(i + firstI - 1) % 26];
                }
                break;
            case 2:
                if(input == iterating) {
                    ++secondI;
                    return rotor2[(i + secondI - 1) % 26];
                }
                break;
            case 3:
                if(input == iterating) {
                    ++thirdI;
                    return rotor3[(i + thirdI - 1) % 26];
                }
                break;
        }
        ++iterating;
    }

    return input;
}

int isValidChar(const char input) {
    return input > 40 && input < 91;
}

int main(int argc, char* argv[]) {
    char mode;
    scanf(" %c", &mode);

    char buffer[1024];
    scanf(" %s", buffer);

    scanf("%i %i %i\n", &firstI, &secondI, &thirdI);

    int counter = 0;

    char switchBuffer[676];

    switchBuffer[0] = '\0';
    switchBuffer[sizeof(switchBuffer) - 1] = ~'\0';

    switches = fgets(switchBuffer, sizeof(switchBuffer), stdin);

    for(char* c = buffer; *c != '\0'; c++) {
        for(char* d = switches; *d != '\0'; d++) {
            if(*d == *c && isValidChar(*d)) {
                if(isValidChar(*(d - 1)))
                    *c = *(d - 1);
                else
                    *c = *(d + 1);

                break;
            }
        }
    }

    if(mode == 'd') {
        for(int i = 3; i > 0; i--)
            for(char* c = buffer; *c != '\0'; c++)
                *c = getRotorD(i, *c);
    }
    else {
        for(int i = 1; i < 4; i++)
            for(char* c = buffer; *c != '\0'; c++)
                *c = getRotor(i, *c);
    }
    
    for(char* c = buffer; *c != '\0'; c++) {
        for(char* d = switches; *d != '\0'; d++) {
            if(*d == *c && *d != ' ') {
                if(d - 1 && *(d - 1) != ' ')
                    printf("%c ", *(d - 1));
                else
                    *c = *(d + 1);

                break;
            }
        }
    }

    if(mode == 'd')
        printf("Die entschluesselte Nachricht ist: %s\n", buffer);
    else
        printf("Die verschluesselte Nachricht ist: %s\n", buffer);
    
    return 0;
}
