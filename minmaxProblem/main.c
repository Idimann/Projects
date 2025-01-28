#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

long maximum(long first, long second) {
    return first > second ? first : second;
}

long maximumCool(int* array, long size) {
    long returning = array[0];

    for(long i = 1; i < size; i++) {
        if(array[i] > returning)
            returning = array[i];
    }

    return returning;
}

long power(long base, long exponent) {
    if(exponent == 0)
        return 1;
    else if(exponent == 1)
        return base;
    else if(exponent < 0)
        printf("Wut\n");

    long returning = base;

    for(long i = 1; i < exponent; i++)
        returning *= base;

    return returning;
}

float calc(long min, long max, long gens) {
    long counter = 0;
    float result = 0;

    for(long i = 0; i < power(max - min + 1, gens); i++) {
        int* array = malloc(gens * sizeof(int));

        for(long j = 0; j < gens; j++)
            array[j] = (i / power(max - min + 1, j)) % (max - min + 1) + min;

        result += maximumCool(array, gens);
        ++counter;

        free(array);
    }

    return result / counter;
}

int main(int argc, char** argv) {
    int min, max;
    int min2, max2;
    char mode;

    printf("Input: $mode$ $minimum$ $maximum$\n");
    scanf("%c %i %i", &mode, &min, &max);

    switch(mode) {
        case 'P':
            printf("Input: $minimum2$ $maximum2$\n");
            scanf("%i %i", &min2, &max2);
            for(int i = min2; i <= max2; i++)
                printf("%i=>%f\n", i, calc(min, max, i));
            break;
        case 'p':
            printf("Input: $limit$ $gens$\n");
            scanf("%i %i", &min2, &max2);
            for(int i = 0; i <= min2; i++)
                printf("%i|%i=>%f\n", min + i, max + i, calc(min + i, max + i, max2));
            break;
        case 'V':
            printf("Input: $limit$ $gens$\n");
            scanf("%i %i", &min2, &max2);
            for(int i = 0; i <= min2; i++)
                printf("%i|%i=>%f\n", min, max + i, calc(min, max + i, max2));
            break;
        case 'v':
            printf("Input: $limit$ $gens$\n");
            scanf("%i %i", &min2, &max2);
            for(int i = 0; i <= min2; i++)
                printf("%i|%i=>%f\n", min + i, max, calc(min + i, max, max2));
            break;
    }

    return 0;
}
