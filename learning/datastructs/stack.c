#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    struct Node* next;
};

void push(struct Node** head, const int pushing) {
    struct Node** prevHead = head;

    struct Node* newHead = malloc(sizeof(struct Node));
    newHead->next = *prevHead;
    newHead->value = pushing;

    *head = newHead;
}

void pop(struct Node** head) {
    if((*head)->next == NULL)
        return;

    struct Node* prevHead = *head;
    *head = (*head)->next;

    free(prevHead);
}

void print(struct Node* head) {
    printf("%i\n", head->value);
}

int main(int argc, char* argv[]) {
    int input;

    struct Node* head = malloc(sizeof(struct Node));

    head->value = 0;
    head->next = NULL;

    for(;;) {
        printf("\nWhat do you want to do?\n[1] Push\n[2] Pop\n[3] Print\n[4] Quit\n\n");

        scanf(" %i", &input);

        switch(input) {
            case 1:
                scanf(" %i", &input);
                push(&head, input);        
                break;
            case 2:
                pop(&head);
                break;
            case 3:
                print(head);
                break;
            case 4:
                return 0;
        }
    }
}
