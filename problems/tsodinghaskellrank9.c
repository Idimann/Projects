#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int arrSize;
    int refusing;
    scanf(" %i %i", &arrSize, &refusing);

    int array[arrSize];
    for(int i = 0; i < arrSize; i++)
        scanf(" %i", &array[i]);

    int expected;
    scanf(" %i", &expected);

    int output = 0;
    for(int i = 0; i < arrSize; i++)
        if(i != refusing)
            output += array[i];

    if(output / arrSize == expected)
        printf("Bon Appetit\n");
    else
        printf("%i\n",  expected - output / arrSize);

    return 0;
}
