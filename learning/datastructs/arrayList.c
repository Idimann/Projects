#include <stdio.h>
#include <stdlib.h>

int arrSize = 0;

void changeSize(const int size, int* array) {
    if(size > 0)
        ++arrSize;
    else
        --arrSize;

    array = malloc((arrSize + size) * sizeof(int));
}

void add(int* array, const int number) {
    changeSize(1, array);

    array[arrSize - 1] = number;
}

void insert(int* array, const int number, const int position) {
    changeSize(1, array);
    if(position == arrSize - 1)
        array[arrSize - 1] = number;
    else {
        for(int i = arrSize - 1; i > position - 1; i--)
            array[i] = array[i - 1];

        array[position] = number;
    }
}

void removeC(int* array, const int element) {
    for(int i = element; i < arrSize; i++) {
        if(i != arrSize - 1)
            array[i] = array[i + 1];
    }

    changeSize(-1, array);
}

void removeE(int* array, const int element) {
    for(int i = 0; i < arrSize; i++) {
        if(array[i] == element) {
            removeC(array, i);
            return;
        }
    }
}

void print(int* array) {
    if(arrSize == 0) {
        printf("The list is empty!\n");
        return;
    }

    for(int i = 0; i < arrSize; i++)
        printf("%i ", array[i]);

    printf("\n");
}

int main(int argc, char* argv[]) {
    int array[] = {};

    int input;
    int input2;

    for(;;) {
        printf("\nWhat do you want to do?\n[1] Add\n[2] Insert\n[3] Remove\n[4] Remove Element\n[5] Print\n[6] Quit\n\n");

        scanf(" %i", &input);

        switch(input) {
            case 1:
                scanf(" %i", &input);
                add(array, input);
                break;
            case 2:
                scanf(" %i %i", &input, &input2);
                insert(array, input, input2);
                break;
            case 3:
                scanf(" %i", &input);
                removeC(array, input);
            case 4:
                scanf(" %i", &input);
                removeE(array, input);
            case 5:
                print(array);
                break;
            case 6:
                return 0;
        }
    }    
}
