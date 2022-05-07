#include <stdio.h>
#include <stdlib.h>

//Edited: 28/2/2022
//Linked List implementation with corresponding tail pointer in C
//
//Implementations:
// createNode()
// push()
// pop()
// popEnd()
// append()
// insertAfter()
// insertBefore()
// sortedInsert()
// findFirstKey()
// findPos()
// del()
// printList()
// printPointers()
// emptyList()
// createList()
// reverse()

struct Node
{
    int value;
    struct Node* next;
};

struct Node* createNode(int newValue)
{
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->value = newValue;
    newNode->next = NULL;

    return newNode;
}

void push(struct Node** head, struct Node** tail, int newValue)
{
    struct Node* newNode = createNode(newValue);

    if (*head == NULL)
    {
        *head = newNode;
        *tail = newNode;
    }
    else
    {
        newNode->next = *head;
        *head = newNode;
    }
}

int pop(struct Node** head, struct Node** tail)
{
    int poppedValue = -1;

    if (*head == NULL)
    {
        printf("List is empty.\n");
    }
    //Do NOT use head == tail, a pointer to a pointer cannot be compared
    //even if the pointer they point to both point to the same memory,
    //the pointers THEMSELVES are in different memory locations.
    else if (*head == *tail)
    {
        poppedValue = (*head)->value;

        free(*head);

        *head = NULL;
        *tail = NULL;
    }
    else
    {
        struct Node* nextNode = (*head)->next;
        poppedValue = (*head)->value;

        free(*head);

        *head = nextNode;
    }

    return poppedValue;
}

//popEnd() is O(n) without a doubly linked list
int popEnd(struct Node** head, struct Node** tail)
{
    int poppedValue = -1;

    if (*head == NULL)
    {
        printf("List is empty.\n");
    }
    else if (*head == *tail)
    {
        poppedValue = (*head)->value;

        free(*head);

        *head = NULL;
        *tail = NULL;
    }
    else
    {
        struct Node* prevNode = *head;

        while (prevNode->next != *tail)
        {
            prevNode = prevNode->next;
        }

        prevNode->next = NULL;

        poppedValue = (*tail)->value;
        free(*tail);
        *tail = prevNode;
    }

    return poppedValue;
}

void append(struct Node** head, struct Node** tail, int newValue)
{
    struct Node* newNode = createNode(newValue);

    if (*head == NULL)
    {
        *head = newNode;
        *tail = newNode;
    }
    else
    {
        (*tail)->next = newNode;
        *tail = newNode;
    }
}

//Breaks sortedInsert() since it unsorts the array.
void insertAfter(struct Node** tail, struct Node* n, int newValue)
{
    if (n == NULL)
        return;

    struct Node* newNode = createNode(newValue);

    newNode->next = n->next;
    n->next = newNode;

    if (n == *tail)
        *tail = newNode;
}

//Insert before is O(n) without a doubly linked list
//Breaks sortedInsert() since it unsorts the array.
void insertBefore(struct Node** head, struct Node* n, int newValue)
{
    if (n == NULL)
        return;

    struct Node* newNode = createNode(newValue);

    if (n == *head)
    {
        newNode->next = *head;
        *head = newNode;
    }
    else
    {
        struct Node* prevNode = *head;

        while(prevNode->next != n)
        {
            prevNode = prevNode->next;
        }

        newNode->next = n;
        prevNode->next = newNode;
    }
}

struct Node* findFirstKey(struct Node* head, int key)
{
    while (head != NULL && head->value != key)
    {
        head = head->next;
    }

    if (head == NULL)
        printf("Error: Key [%d] not found!\n", key);

    return head;
}

struct Node* findPos(struct Node* head, int pos)
{
    for (int i=0; i<pos && head!=NULL; ++i)
    {
        head = head->next;
    }

    if (head == NULL)
        printf("Error: Position [%d] out of bounds!\n", pos);

    return head;
}

void del(struct Node** head, struct Node** tail, struct Node* n)
{
    if (n == NULL)
        return;

    if(n == *head && *head  == *tail)
    {
        *head = NULL;
        *tail = NULL;
        free(n);
    }
    else if (n == *head)
    {
        *head = (*head)->next;
        free(n);
    }
    else
    {
        struct Node* prevNode = *head;

        while (prevNode->next != n)
        {
            prevNode = prevNode->next;
        }

        prevNode->next = n->next;

        if (n == *tail)
            *tail = prevNode;

        free(n);
    }
}

void printList(struct Node* head)
{
    if (head == NULL)
        return;

    struct Node* tmp = head;

    printf("List: [");
    while (tmp->next != NULL)
    {
        printf("%d -> ", tmp->value);
        tmp = tmp->next;
    }
    printf("%d]\n", tmp->value);
}

void printPointers(struct Node* head, struct Node* tail)
{
    if (head == NULL && tail == NULL)
    {
        printf("Empty list.\n");
    }
    else
    {
        printf("Head address: %p | Value: %d\n", (void*)head, head->value);
        printf("Tail address: %p | Value: %d\n", (void*)tail, tail->value);
    }
}

void emptyList(struct Node** head, struct Node** tail)
{
    while (*head != NULL)
    {
        pop(head, tail);
    }
}

void createList(int* arr, int size, struct Node** head, struct Node** tail)
{
    emptyList(head, tail);
    for (int i=0; i<size; ++i)
    {
        append(head, tail, arr[i]);
    }
}

//Assumes the linked list has NOT been modified manually
//Sorts the array ascending
void sortedInsert(struct Node** head, struct Node** tail, int newValue)
{
    struct Node* newNode = createNode(newValue);

    if (*head == NULL)
    {
        *head = newNode;
        *tail = newNode;
    }
    else if ((*head)->value > newValue)
    {
        newNode->next = *head;
        *head = newNode;

    }
    else if ((*tail)->value <= newValue)
    {
        (*tail)->next = newNode;
        *tail = newNode;
    }
    else
    {
        struct Node* tmp = *head;
        while (tmp->next!=NULL && tmp->next->value < newValue)
        {
            tmp = tmp->next;
        }
        newNode->next = tmp->next;
        tmp->next = newNode;
    }
}

void reverse(struct Node** head, struct Node** tail)
{
    struct Node* prevNode = NULL;
    struct Node* nextNode = NULL;
    struct Node* currNode = *head;

    while (currNode!=NULL)
    {
        nextNode = currNode->next;
        currNode->next = prevNode;
        prevNode = currNode;
        currNode = nextNode;
    }

    *tail = *head;
    *head = prevNode;
}

int main()
{
    //Checking the functions:
    struct Node* head = NULL;
    struct Node* tail = NULL;

    for (int i=10; i>=0; --i)
    {
        sortedInsert(&head, &tail, i);
    }

    printList(head);

    reverse(&head, &tail);

    printPointers(head, tail);

    printList(head);


//    push(&head, &tail, 1);
//    printPointers(head, tail);
//    del(&head, &tail, findPos(head, 0));
//    printList(head);
//    printPointers(head, tail);
//    printf("\n");
//
//    int arr[10] = {1, 4, 4, 5, 6, 7, 8, 9, 10, 12};
//    createList(arr, 10, &head, &tail);
//
//    insertAfter(&tail, findFirstKey(head, 12), 32);
//    insertAfter(&tail, findFirstKey(head, 89), 32);
//    insertAfter(&tail, findFirstKey(head, 4), 32);
//
//    insertBefore(&head, findFirstKey(head, 1), 32);
//    insertBefore(&head, findPos(head, 0), 32);
//    insertBefore(&head, findPos(head, 20), -32);
//
//    for (int i=0; i<5; ++i)
//    {
//        append(&head, &tail, i);
//        push(&head, &tail, i);
//    }
//
//    for (int j=0; j<4; ++j)
//    {
//        int p = pop(&head, &tail);
//        int pEnd = popEnd(&head, &tail);
//        printf("Popped: %d\n", p);
//        printf("Popped: %d\n", pEnd);
//    }
//
//    printList(head);
//    del(&head, &tail, findPos(head, 0));
//
//    printList(head);
//    del(&head, &tail, findPos(head, 15));
//
//    printList(head);
//    del(&head, &tail, findPos(head, 4));
//
//    int arr2[1] = {0};
//    createList(arr2, 1, &head, &tail);
//
//    printf("\n");
//    printList(head);
//    printf("\n");
//    printPointers(head, tail);
}
