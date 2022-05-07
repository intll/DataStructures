#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int value;
    struct Node* next;
    struct Node* prev;
};

void swap(struct Node** a, struct Node** b)
{
    struct Node* c = *a;
    *a=*b;
    *b=c;
}

struct Node* createNode(int newValue)
{
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->value = newValue;
    newNode->next = NULL;
    newNode->prev = NULL;

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
        (*head)->prev = newNode;
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
    else if (*head == *tail)
    {
        poppedValue = (*head)->value;

        free(*head);

        *head = NULL;
        *tail = NULL;
    }
    else
    {
        poppedValue = (*head)->value;
        *head = (*head)->next;
        free((*head)->prev);
        (*head)->prev = NULL;
    }

    return poppedValue;
}

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
        poppedValue = (*tail)->value;
        *tail = (*tail)->prev;
        free((*tail)->next);
        (*tail)->next = NULL;
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
        newNode->prev = *tail;
        *tail = newNode;
    }
}

void insertAfter(struct Node** tail, struct Node* n, int newValue)
{
    if (n == NULL)
        return;
    else
    {
        struct Node* newNode = createNode(newValue);

        newNode->prev = n;
        newNode->next = n->next;
        n->next->prev = newNode;
        n->next = newNode;

        //Still buggy!
        if (n == *tail)
        {
             *tail = newNode;
             return;
        }
    }
}

void insertBefore(struct Node** head, struct Node* n, int newValue)
{
    if (n == NULL)
        return;
    else
    {
        struct Node* newNode = createNode(newValue);

        newNode->prev = n->prev;
        newNode->next = n;
        n->prev = newNode;

        if (n == *head)
        {
            *head = newNode;
            return;
        }

        newNode->prev->next = newNode;
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
    else if (n == *head && *head == *tail)
    {
        *head = NULL;
        *tail = NULL;
        free(n);
    }
    else if(n == *head)
    {
        *head = (*head)->next;
        (*head)->prev = NULL;
        free(n);
    }
    else if (n == *tail)
    {
        *tail = (*tail)->prev;
        (*tail)->next = NULL;
        free(n);
    }
    else
    {
        (n->prev)->next = n->next;
        (n->next)->prev = n->prev;
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
        printf("%d <-> ", tmp->value);
        tmp = tmp->next;
    }
    printf("%d]\n", tmp->value);
}

void printReverse(struct Node* tail)
{
    if (tail == NULL)
        return;

    struct Node* tmp = tail;

    printf("List: [");
    while (tmp->prev != NULL)
    {
        printf("%d <-> ", tmp->value);
        tmp = tmp->prev;
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

//Sorted ascending
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
        (*head)->prev = newNode;
        newNode->next = *head;
        *head = newNode;
    }
    else if ((*tail)->value <= newValue)
    {
        (*tail)->next = newNode;
        newNode->prev = *tail;
        *tail = newNode;
    }
    else
    {
        struct Node* tmp = *head;

        while (tmp->next!=NULL && tmp->next->value < newValue)
        {
            tmp = tmp->next;
        }

        newNode->prev = tmp;
        newNode->next = tmp->next;
        tmp->next->prev = newNode;
        tmp->next = newNode;
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

void reverse(struct Node** head, struct Node** tail)
{
    struct Node* currNode = *head;

    while (currNode!=NULL)
    {
        swap(&currNode->next, &currNode->prev);
        currNode = currNode->prev;
    }

    swap(head, tail);
}

int main()
{
    struct Node* head = NULL;
    struct Node* tail = NULL;

    sortedInsert(&head, &tail, 5);
    sortedInsert(&head, &tail, 10);
    sortedInsert(&head, &tail, 15);
    sortedInsert(&head, &tail, 100);
    sortedInsert(&head, &tail, 90);
    printList(head);
}
