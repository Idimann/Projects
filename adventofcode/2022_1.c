#include <stdio.h>
#include <stdlib.h>

int power(const int input, const int exp) {
    int returning = input;

    for(int i = 1; i < exp; i++) {
        returning *= input;
    }

    return returning;
}

unsigned int parse(char* input) {
    int returning = 0;

    int counter = 0;
    int size = 0;
    
    for(char* c = input; *c != '\0'; c++)
        ++size;
    
    for(char* c = input; *c != '\0'; c++) {
        returning += (*c - 48) * power(10, size - counter);

        ++counter;
    }

    return returning / 10;
}

int getResult(int input[]) {
    int returning = 0;
    int current = 0;

    for(int i = 0; i < sizeof(input) / sizeof(int); i++) {
        switch(i) {
            case -1:
                if(current > returning)
                    returning = current;
                
                current = 0;
                break;
            default:
                current += input[i];
                break;
        }
    }

    if(current > returning)
        returning = current;

    return returning;
}

int main(int argc, char* argv[]) {
    int input[] = {1000, 2000, 3000, -1, 4000, -1, 5000, 6000, -1, 7000, 8000, 9000, -1, 10000};
    printf("%i", getResult(input));
    return 0;
}
