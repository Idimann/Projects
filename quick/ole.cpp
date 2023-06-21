#include <stdio.h>
#include <time.h>
#include <random>

int main(int argc, char* argv[]) {
    int steps = 3;
    int input;

    srand(time(NULL));
    do {
        scanf(" %i", &input);

        if(input == rand() % steps) {
            switch(steps) {
                case 3:
                    steps = 5;
                    break;
                case 5:
                    steps = 10;
                    break;
                case 10:
                    steps = 11;
                    break;
            }
            printf("Gut!\n");
        }
        else {
            printf("Schlecht!\n");
            steps = 3;
        }
    } while(steps != 11);

    printf("Hammer!\n");
    return 0;
}
