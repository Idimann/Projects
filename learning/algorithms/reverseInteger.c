#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char* argv[]) {
    int input;
    scanf(" %i", &input);

    int output = 0;

    int numbers = 0;
    int countInput = (input < 0) ? -input : input;

    while(countInput > 0) {
        ++numbers;
        countInput /= 10;
    }

    int counter = 0;
    countInput = (input < 0) ? -input : input;

    while(countInput > 0) {
        output += (countInput % 10) * pow(10, numbers - counter);

        countInput /= 10;
        ++counter;
    }

    output /= 10;
    output = (input < 0) ? -output : output;

    printf("%i\n", output);

    return 0;
}
