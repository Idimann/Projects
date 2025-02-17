#include <stdio.h>
#include <stdlib.h>

const float changing = 1e-3;
const int number = 20;

float cost(const float approximation, float data[][2]) {
    float returning = 0;

    for(int i = 0; i < number; i++) {
        returning += (approximation * data[i][0] - data[i][1]) *
            (approximation * data[i][0] - data[i][1]);
    }

    return returning / number;
}

int main(int argc, char* argv[]) {
    srand(500);

    float data[number][2];

    for(int i = 0; i < number; i++) {
        data[i][0] = i;
        data[i][1] = i - 25;
    }

    float approximation = (rand() / RAND_MAX) * 100.0f;

    int iterations = 0;

    while(cost(approximation, data) >= changing) {
        approximation -= (cost(approximation, data) -
                cost(approximation - changing, data)) * changing;

        ++iterations;

        if(cost(approximation, data) <= cost(approximation - changing, data) &&
                cost(approximation, data) <= cost(approximation + changing, data))
            break;

        if(iterations % 100000 == 0)
            printf("%f\n", approximation);
    }

    printf("Got %f in %i iterations\n", approximation, iterations);

    return 0;
}
