#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    int element;
    struct node* next;
};

void add(struct node* head, const int element) {
    struct node* pointer = head;

    while(pointer != NULL && pointer->next != NULL)
        pointer = pointer->next;
    
    pointer->next = (struct node*) malloc(sizeof(struct node));

    pointer->next->element = element;
    pointer->next->next = NULL;
}

void insert(struct node* head, const int element, const int position) {
    struct node* pointer = head;

    int counter = 0;

    while(pointer != NULL && pointer->next != NULL && counter != position) {
        pointer = pointer->next;
        ++counter;
    }
    
    struct node* prevPointer = pointer->next;
    pointer->next = (struct node*) malloc(sizeof(struct node));

    pointer->next->element = element;
    pointer->next->next = prevPointer;
}

void removeE(struct node* head, const int element) {
    struct node* pointer = head;

    while(pointer != NULL && pointer->next != NULL && pointer->next->element != element)
        pointer = pointer->next;
    
    struct node* prevPtr = pointer->next;
    pointer->next = pointer->next->next;

    free(prevPtr);
}

void removeC(struct node* head, const int element) {
    struct node* pointer = head;

    int counter = 0;

    while(pointer != NULL && pointer->next != NULL && counter != element) {
        pointer = pointer->next;
        ++counter;
    }
    
    struct node* prevPtr = pointer->next;
    pointer->next = pointer->next->next;

    free(prevPtr);
}

void print(struct node* head) {

    if(head->next == NULL) {
        printf("The list is empty\n");
        return;
    }
    
    for(struct node* pointer = head->next; pointer != NULL; pointer = pointer->next)
        printf("%i ", pointer->element);

    printf("\n");
}

int main(int argc, char *argv[]) {
    struct node* head = malloc(sizeof(struct node));

    head->element = 0;
    head->next = NULL;

    int input;
    int input2;
    
    for(;;) {
        printf("\nWhat do you want to do?\n[1] Add\n[2] Insert\n[3] Remove Element\n[4] Remove\n[5] Print\n[6] Quit\n\n");

       scanf(" %i", &input);

       int quit = 0;

       switch(input) {
            case 1:
                scanf(" %i", &input);
                add(head, input);
                break;
            case 2:
                scanf(" %i %i", &input, &input2);
                insert(head, input, input2);
                break;
            case 3:
                scanf(" %i", &input);
                removeE(head, input);
                break;
            case 4:
                scanf(" %i", &input);
                removeC(head, input);
                break;
            case 5:
                print(head);
                break;
            case 6:
                quit = 1;
       }

       if(quit)
           return 0;

    }
    return 0;
}
