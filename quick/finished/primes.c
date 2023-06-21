#include <stdio.h>

int main(int argc, char* argv[]) {
    int input;
    scanf(" %i", &input);

    int output = (input > 2) + (input > 3);

    for(int i = 4; i < input; i++) {
        int isPrime = 1;
        for(int j = 2; j < i; j++)
            if(i % j == 0) {
                isPrime = 0;
                break;
            }

        output += isPrime;
    }

    printf("%i\n", output);

    return 0;
}
