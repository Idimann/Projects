#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int m;
    int n;
    float* numbers;
} matrix_f;

void setElement(matrix_f* matrix, int i, int j, float setting) {
    if(i >= matrix->m || j >= matrix->n) {
        printf("Fuck\n");
        return;
    }

    matrix->numbers[i * matrix->n + j] = setting;
}

float giveElement(matrix_f* matrix, int i, int j) {
    if(i >= matrix->m || j >= matrix->n) {
        printf("Fuck\n");
        return 0;
    }

    return matrix->numbers[i * matrix->n + j];
}

matrix_f* inputMatrix() {
    matrix_f* output = malloc(sizeof(matrix_f));
    printf("Size (mxn): ");
    scanf("%ix%i", &output->m, &output->n);
    printf("\n");
    if(output->m <= 0 || output->n <= 0) {
        printf("Idiot\n");
        exit(0);
    }
    output->numbers = malloc(sizeof(float) * output->m * output->n);

    for(int i = 0; i < (output->m); i++) {
        for(int j = 0; j < (output->n); j++) {
            float input = 0;
            if(i == output->m - 1 && j == output->n - 1)
                scanf("%f", &input);
            else if(j == output->n -1) {
                char next = 0;
                char next2 = 0;
                scanf("%f %c %c", &input, &next, &next2);

                if(next != '\\' || next2 != '\\')
                    printf("Strange linebreak\n");
            }
            else {
                char next = 0;
                scanf("%f %c", &input, &next);

                if(next != '&')
                    printf("Strange\n");
            }

            setElement(output, i, j, input);
        }
    }

    return output;
}

void outputMatrix(matrix_f* matrix) {
    for(int i = 0; i < (matrix->m); i++) {
        for(int j = 0; j < (matrix->n); j++) {
            printf("%1.2f", giveElement(matrix, i, j));

            if(j != matrix->n - 1)
                printf(" & ");
        }

        if(i != matrix->m - 1)
            printf(" \\\\\n");
    }

    printf("\n");
}

matrix_f* multiply(matrix_f* matrix1, matrix_f* matrix2) {
    if(matrix1->n != matrix2->m) {
        printf("Matrices aren't fit for multiplication\n");
        exit(0);
    }

    matrix_f* output = malloc(sizeof(matrix_f));
    output->m = matrix1->m;
    output->n = matrix2->n;
    output->numbers = malloc(sizeof(float) * output->m * output->n);

    for(int i = 0; i < (output->m); i++) {
        for(int j = 0; j < (output->n); j++) {
            float setting = 0;

            for(int x = 0; x < (matrix1->n); x++)
                setting += giveElement(matrix1, i, x) * giveElement(matrix2, x, j);

            setElement(output, i, j, setting);
        }
    }

    return output;
}

int main(int argc, char** argv) {
    matrix_f* matrix1 = inputMatrix();
    matrix_f* matrix2 = inputMatrix();

    outputMatrix(multiply(matrix1, matrix2));

    return 0;
}
