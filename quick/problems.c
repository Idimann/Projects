#include <stdio.h>

enum test {
    TEST,
    LOL
};

int main(int argc, char* argv[]) {
    int number;
    scanf("%i", &number);

    int sum;
    
    while(number) {
        sum += number % 10;
        number /= 10;
    }

    if(sum % 2 == 0)
        printf("Evenish\n");
    else
        printf("Oddish\n");

    return 0;
}
