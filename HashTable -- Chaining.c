#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct Node
{
    char str[20];

    struct Node* next;
};

int hash(char* str, int tableSize)
{
    int hash=0;
    for (int i=0; str[i]!='\0'; ++i)
    {
        hash+=str[i];
    }

    return hash%tableSize;
}

struct Node* createNode(char* str)
{
    struct Node* newNode = malloc(sizeof(struct Node));
    strcpy(newNode->str, str);
    newNode->next = NULL;

    return newNode;
}

void insert(struct Node* arr[], struct Node* n, int tableSize)
{
    int hashKey = hash(n->str, tableSize);

    if (arr[hashKey] == NULL)
    {
        arr[hashKey] = n;
    }
    else
    {
        if (strcmp(arr[hashKey]->str, n->str) > 0)
        {
            n->next = arr[hashKey];
            arr[hashKey] = n;
        }
        else
        {
            struct Node* curr = arr[hashKey];

            while (curr->next!=NULL && strcmp(curr->next->str, n->str) < 0)
            {
                curr = curr->next;
            }

            n->next = curr->next;
            curr->next = n;
        }
    }
}

void del(struct Node* arr[], struct Node* n, int tableSize)
{
    if (n==NULL)
        return;
    else
    {
        int hashKey=hash(n->str, tableSize);

        if (arr[hashKey] == n)
        {
            arr[hashKey] = n->next;
        }
        else
        {
            struct Node* curr = arr[hashKey];
            while (curr->next!=n)
            {
                curr = curr->next;
            }
            curr->next = n->next;
        }

        free(n);
    }
}

struct Node* searchStr(struct Node* arr[], char* str, int tableSize)
{
    int hashKey=hash(str, tableSize);

    struct Node* curr = arr[hashKey];

    while (curr!=NULL && strcmp(curr->str, str)!=0)
    {
        curr = curr->next;
    }

    if (curr == NULL)
    {
        printf("String not found in table!\n");
    }
    else
    {
        printf("String found in index [%d]!\n", hashKey);
    }

    return curr;
}

void printTable(struct Node* arr[], int tableSize)
{
    for (int i=0; i<tableSize; ++i)
    {
        printf("[%d] %s", i, arr[i]==NULL ? "~" : arr[i]->str);

        if (arr[i]!=NULL)
        {
            struct Node* curr = arr[i]->next;
            while (curr!=NULL)
            {
                printf(" -> %s", curr->str);
                curr = curr->next;
            }
        }

        printf("\n");
    }
}

int main()
{
    const int size = 10;
    struct Node* arr[10] = {0};
    char str[20];

    srand(time(NULL));


    for (int j=0; j<100; ++j)
    {
        char randStr[20];
        for (int i=0; i<5; ++i)
        {
            randStr[i] = (char)((rand()%26)+'a');
        }
        insert(arr, createNode(randStr), size);
    }



    int c=0;

    while (c!=4)
    {
        system("CLS");

        printf("Table:\n");
        printTable(arr, 10);
        printf("\n\n");

        printf("1. Insert\n");
        printf("2. Search\n");
        printf("3. Delete\n");
        printf("4. Exit\n");

        scanf("%d", &c);

        switch (c)
        {
        case 1:
            printf("Enter a string to be inputted:\n >> ");
            scanf(" %[^\n]", str);
            insert(arr, createNode(str), size);
            break;
        case 2:
            printf("Enter a string to be searched:\n >> ");
            scanf(" %[^\n]", str);
            searchStr(arr, str, size);
            system("PAUSE");
            break;
        case 3:
            printf("Enter a string to be deleted:\n >> ");
            scanf(" %[^\n]", str);
            del(arr, searchStr(arr, str, size), size);
            system("PAUSE");
            break;
        case 4:
            return 0;
        default:
            printf("Invalid input!\n");
            system("PAUSE");
            break;
        }
    }
}
