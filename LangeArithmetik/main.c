#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

typedef struct {
    unsigned char* bytes;
    int size;
    char sign;
} Num;

Num createNum(int size) {
    Num returning = {};
    returning.size = size;
    returning.sign = 0;
    returning.bytes = malloc(size * sizeof(unsigned char));

    return returning;
}

Num copyNum(Num* num) {
    Num returning = createNum(num->size);
    returning.sign = num->sign;
    memcpy(returning.bytes, num->bytes, num->size * sizeof(unsigned char));

    return returning;
}

void deleteNum(Num num) {
    free(num.bytes);
}

void setNum(Num* num, long number, int size) {
    if(number < 0) {
        num->sign = 1;
        number = -number;
    }
    num->size = size;

    for(int i = 0; i < (num->size); i++)
        num->bytes[i] = ((unsigned char*) &number)[i];
}

void shiftNum(Num* num, int times) {
    Num copy = copyNum(num);
    deleteNum(*num);
    *num = createNum(copy.size + times);

    memcpy(&num->bytes[times], copy.bytes, copy.size * sizeof(unsigned char));
}

void printNum(Num* num, char end) {
    if(num->sign)
        printf("-");

    for(int i = (num->size) - 1; i >= 0; i--) {
        for(int j = 7; j >= 0; j--)
            printf("%i", 0x1 & (num->bytes[i] >> j));

        if(i != 0)
            printf("|");
    }

    if(end)
        printf("\n");
}

int greaterEq(Num first, Num second) {
    if(first.size != second.size)
        return first.size > second.size;

    for(int i = 1; i <= first.size; i++)
        if(first.bytes[first.size - i] != second.bytes[second.size - i])
            return first.bytes[first.size - i] > second.bytes[second.size - i];
    
    return 1;
}

void realAdd(Num* first, Num second) {
    unsigned short remainder = 0;
    for(int i = 0; i < (first->size); i++) { //LSP said i should put brackets, dk why
        unsigned short f = first->bytes[i];
        unsigned short s = second.bytes[i];

        first->bytes[i] = (unsigned char) (f + s + remainder);
        remainder = (f + s + remainder) / 256;
    }

    if(remainder) {
        Num helper = *first;
        *first = createNum(helper.size + 1);
        memcpy(first->bytes, helper.bytes, helper.size * sizeof(unsigned char));

        first->bytes[helper.size] = remainder;
        deleteNum(helper);
    }
}

void realSubtract(Num* first, Num second) {
    unsigned char remainder = 0;
    for(int i = 0; i < (first->size); i++) { //LSP said i should put brackets, dk why
        unsigned short f = first->bytes[i];
        unsigned short s = second.bytes[i];

        first->bytes[i] = (unsigned char) (f - s - remainder);
        remainder = (f - s - remainder) / 256;
    }
}

void add(Num* first, Num second) {
    if(first->size < second.size) {
        Num helper = copyNum(first);
        *first = copyNum(&second);
        second = helper;
    }

    if(first->sign == 0 && second.sign == 0)
        realAdd(first, second);
    else if(first->sign == 1 && second.sign == 1) {
        realAdd(first, second);
        first->sign = 1;
    }
    else if(greaterEq(*first, second))
        realSubtract(first, second);
    else if(greaterEq(second, *first)) {
        realSubtract(&second, *first);
        *first = copyNum(&second);
    }
}

void multiply(Num* first, Num second) {
    if(first->size < second.size) {
        Num helper = *first;
        *first = second;
        second = helper;
    }

    Num returning = createNum(first->size);
    setNum(&returning, 0, first->size);
    Num created = createNum(2);

    for(int i = 0; i < (first->size); i++) {
        for(int j = 0; j < (second.size); j++) {
            setNum(&created, first->bytes[i] * second.bytes[j], 2);
            if(i + j)
                shiftNum(&created, i + j);

            add(&returning, created);
        }
    }

    deleteNum(created);
    *first = returning;
}

int main(int argc, char** argv) {
    Num first = createNum(1);
    Num second = createNum(1);
    setNum(&first, 64, 2);
    setNum(&second, 35, 2);

    add(&first, second);
    //realSubtract(&first, second);
    printNum(&first, 1);

    return 0;
}
