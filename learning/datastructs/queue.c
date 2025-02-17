#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long long C_LENGTH;
unsigned long long Q_SIZE;

typedef struct node {
    int element;
    struct node* next;
} Node_t;

void removeC(Node_t* head, const int element) {
    Node_t* pointer = head;

    int counter = 0;

    while(pointer != NULL && pointer->next != NULL && counter != element) {
        pointer = pointer->next;
        ++counter;

    }
    Node_t* prevPtr = pointer->next;
    pointer->next = pointer->next->next;

    free(prevPtr);
}

void insert(Node_t* head, const int element) {
    Node_t* pointer = head;

    int counter = 0;

    Node_t* prevPointer = pointer->next;
    pointer->next = (Node_t*) malloc(sizeof(Node_t));

    pointer->next->element = element;
    pointer->next->next = prevPointer;

    ++C_LENGTH;

    if(C_LENGTH == Q_SIZE) {
        removeC(head, C_LENGTH - 1);
        --C_LENGTH;
    }
}

void print(Node_t* head) {

    if(head->next == NULL) {
        printf("The queue is empty\n");
        return;
    }
    Node_t* pointer = head;

    for(;pointer->next != NULL; pointer = pointer->next) {}

    printf("%i ", pointer->element);

    printf("\n");
}

int main(int argc, char *argv[]) {
    Node_t* head = malloc(sizeof(Node_t));

    scanf(" %llu", &Q_SIZE);

    ++Q_SIZE;

    head->element = 0;
    head->next = NULL;

    int input;
    int input2;

    for(;;) {
        printf("\nWhat do you want to do?\n[1] Push\n[2] Print\n[3] Quit\n\n");

       scanf(" %i", &input);

       int quit = 0;

       switch(input) {
            case 1:
                scanf(" %i", &input);
                insert(head, input );
                break;
            case 2:
                print(head);
                break;
            case 3:
                quit = 1;
       }

       if(quit)
           return 0;

    }
    return 0;
}

