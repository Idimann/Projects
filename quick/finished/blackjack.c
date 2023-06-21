#include <stdio.h>

int main(int argc, char* argv[]) {
    char* array[] = {"2", "8", "J"};

    int value = 0;

    for(int i = 0; i < 5; i++) {
        if(*array[i] == '10' || *array[i] == 'Q' || *array[i] == 'J' || *array[i] == 'K')
            value += 10;
        else if(*array[i] == '9')
            value += 9;
        else if(*array[i] == '8')
            value += 8;
        else if(*array[i] == '7')
            value += 7;
        else if(*array[i] == '6')
            value += 6;
        else if(*array[i] == '5')
            value += 5;
        else if(*array[i] == '4')
            value += 4;
        else if(*array[i] == '3')
            value += 3;
        else if(*array[i] == '2')
            value += 2;
        else if(*array[i] == 'A')
            value += 1;
    }

    if(value > 21)
        printf("You lost\n");
    else
        printf("You didnt lose\n");

    return 0;
}
