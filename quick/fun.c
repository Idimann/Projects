#include <stdio.h>
#include <math.h>

int main(int argc, char* argv[]) {
    int input;
    scanf(" %i", &input);
    
    int hunderter = floor(input / 100.0);
    int zehner = floor((input - hunderter * 100) / 10.0);
    int einer = input % 10;

    char output[12];
    int outputCounter = -1;

    switch(hunderter) {
        case 0:
            break;
        case 3:
            output[++outputCounter] = 'C';
        case 2:
            output[++outputCounter] = 'C';
        case 1:
            output[++outputCounter] = 'C';
            break;
        case 4:
            output[++outputCounter] = 'C';
        case 5:
            output[++outputCounter] = 'D';
            break;
        case 8:
            output[++outputCounter] = 'D';
            output[++outputCounter] = 'C';
            output[++outputCounter] = 'C';
            output[++outputCounter] = 'C';
            break;
        case 7:
            output[++outputCounter] = 'D';
            output[++outputCounter] = 'C';
            output[++outputCounter] = 'C';
            break;
        case 6:
            output[++outputCounter] = 'D';
            output[++outputCounter] = 'C';
            break;
        case 9:
            output[++outputCounter] = 'C';
            output[++outputCounter] = 'M';
            break;
    }

    switch(zehner) {
        case 0:
            break;
        case 3:
            output[++outputCounter] = 'X';
        case 2:
            output[++outputCounter] = 'X';
        case 1:
            output[++outputCounter] = 'X';
            break;
        case 4:
            output[++outputCounter] = 'X';
        case 5:
            output[++outputCounter] = 'L';
            break;
        case 8:
            output[++outputCounter] = 'L';
            output[++outputCounter] = 'X';
            output[++outputCounter] = 'X';
            output[++outputCounter] = 'X';
            break;
        case 7:
            output[++outputCounter] = 'L';
            output[++outputCounter] = 'X';
            output[++outputCounter] = 'X';
            break;
        case 6:
            output[++outputCounter] = 'L';
            output[++outputCounter] = 'X';
            break;
        case 9:
            output[++outputCounter] = 'X';
            output[++outputCounter] = 'C';
            break;
    }
    
    switch(einer) {
        case 0:
            break;
        case 3:
            output[++outputCounter] = 'I';
        case 2:
            output[++outputCounter] = 'I';
        case 1:
            output[++outputCounter] = 'I';
            break;
        case 4:
            output[++outputCounter] = 'I';
        case 5:
            output[++outputCounter] = 'V';
            break;
        case 8:
            output[++outputCounter] = 'V';
            output[++outputCounter] = 'I';
            output[++outputCounter] = 'I';
            output[++outputCounter] = 'I';
            break;
        case 7:
            output[++outputCounter] = 'V';
            output[++outputCounter] = 'I';
            output[++outputCounter] = 'I';
            break;
        case 6:
            output[++outputCounter] = 'V';
            output[++outputCounter] = 'I';
            break;
        case 9:
            output[++outputCounter] = 'I';
            output[++outputCounter] = 'X';
            break;
    }

    printf("%s\n", output);

    return 0;
}
