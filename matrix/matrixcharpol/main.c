#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint32_t polynom;

typedef struct {
    int m;
    int n;
    polynom* numbers;
} matrix_f;

void setElement(matrix_f* matrix, int i, int j, polynom setting) {
    if(i >= matrix->m || j >= matrix->n) {
        printf("Fuck\n");
        return;
    }

    matrix->numbers[i * matrix->n + j] = setting;
}

polynom giveElement(matrix_f* matrix, int i, int j) {
    if(i >= matrix->m || j >= matrix->n) {
        printf("Fuck\n");
        return 0;
    }

    return matrix->numbers[i * matrix->n + j];
}

polynom polyMult(polynom first, polynom second) {
    polynom result = 0;

    for(int i = 0; i < sizeof(polynom) / sizeof(char); i++) {
        for(int j = 0; j <= i; j++)
            ((char*)(result))[i] += ((char*)(first))[j] * ((char*)(second))[i - j];
    }

    return result;
}

void inputPolynom(polynom* poly) {
    scanf("%i,%i,%i,%i", &(((char*)(poly))[0]), &(((char*)(poly))[1]), (&((char*)(poly))[2]), 
            &(((char*)(poly))[3]));
}

void printPolynom(polynom poly) {
    printf("(");
    int grade = 0;

    for(int i = 0; i < sizeof(polynom) / sizeof(char); i++) {
        if(((char*)(poly))[i] != 0) {
            grade = i;
        }
    }

    for(int i = 0; i < sizeof(polynom) / sizeof(char); i++) { //sizeof(char) because future
        if(((char*)(poly))[i] != 0) {
            printf("%i", ((char*)(poly))[i]);
            if(i != sizeof(polynom) / sizeof(char) - 1 && ((char*)(poly))[i + 1] != 0)
                printf(" +");
        }

        if(i == grade)
            break;
    }

    printf(")");
}

matrix_f* inputMatrix() {
    matrix_f* output = malloc(sizeof(matrix_f));
    printf("Size: ");
    scanf("%i", &output->m);
    output->n = output->m;
    printf("\n");
    if(output->m <= 0 || output->n <= 0) {
        printf("Idiot\n");
        exit(0);
    }
    output->numbers = malloc(sizeof(polynom) * output->m * output->n);

    for(int i = 0; i < (output->m); i++) {
        for(int j = 0; j < (output->n); j++) {
            polynom* input = malloc(sizeof(polynom));
            if(i == output->m - 1 && j == output->n - 1)
                inputPolynom(input);
            else if(j == output->n -1) {
                char next = 0;
                char next2 = 0;
                inputPolynom(input);
                scanf(" %c %c", &next, &next2);

                if(next != '\\' || next2 != '\\')
                    printf("Strange linebreak\n");
            }
            else {
                char next = 0;
                inputPolynom(input);
                scanf(" %c", &next);

                if(next != '&')
                    printf("Strange\n");
            }

            ((char*)(input))[0] *= -1;
            if(i == j)
                ((char*)(input))[1] = 1;

            setElement(output, i, j, *input);

            // TODO: Clear input (I forgot the command)
        }
    }

    return output;
}

void outputMatrix(matrix_f* matrix) {
    for(int i = 0; i < (matrix->m); i++) {
        for(int j = 0; j < (matrix->n); j++) {
            printPolynom(giveElement(matrix, i, j));

            if(j != matrix->n - 1)
                printf(" & ");
        }

        if(i != matrix->m - 1)
            printf(" \\\\\n");
    }

    printf("\n");
}

float det(matrix_f* matrix) {
    if(matrix->m == matrix->n && matrix->m == 1)
        return giveElement(matrix, 0, 0);

    float result = 0;

    for(int i = 0; i < (matrix->n); i++) {
        matrix_f* new = malloc(sizeof(matrix_f));
        new->m = matrix->m - 1;
        new->n = matrix->n - 1;
        new->numbers = malloc(sizeof(polynom) * new->m * new->n);

        for(int r = 1; r < (matrix->m); r++) {
            for(int s = 0; s < (matrix->n); s++) {
                if(s == i)
                    continue;
                setElement(new, r - 1, (s < i) ? s : (s - 1), giveElement(matrix, r, s));
            }
        }

        if(i % 2 == 0)
            result += polyMult(giveElement(matrix, 0, i), det(new));
        else
            result -= polyMult(giveElement(matrix, 0, i), det(new));
    }

    return result;
}

int main(int argc, char** argv) {
    matrix_f* input = inputMatrix();
    printPolynom(det(input));

    return 0;
}
