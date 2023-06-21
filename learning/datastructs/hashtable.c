#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long long SIZE = 20;

void add(int* array, const int number, const int position) {
    array[position] = number;
}

void print(int* array, int element) {
    printf("%i\n", array[element]);
}

unsigned long hash(char* pointer) {
    int strleng = strlen(pointer);

    unsigned long long returning = 0;

    for(int i = 0; i < strleng; i++) {
        returning += (strleng - i) * 27 * pointer[i]; 
    }

    return returning % SIZE;
}

int main(int argc, char* argv[]) {
    printf("Input the table size: ");
    scanf(" %llu", &SIZE);

    int* array = malloc(sizeof(int) * SIZE);

    int input;
    char input2[1024];

    for(;;) {
        printf("\nWhat do you want to do?\n[1] Hash\n[2] Output\n[3] Quit\n\n");

        scanf(" %i", &input);

        switch(input) {
            case 1:
                scanf(" %i", &input);
                scanf(" %s", input2);
                add(array, input, hash(input2));
                break;
            case 2:
                scanf(" %s", input2);
                print(array, hash(input2));
                break;
            case 3:
                return 0;
        }
    }    
}
