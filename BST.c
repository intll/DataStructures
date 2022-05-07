#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int value;
    struct Node* right;
    struct Node* left;
};

struct Node* createNode(int newValue)
{
    struct Node* newNode = malloc(sizeof(struct Node));

    newNode->value = newValue;
    newNode->right = NULL;
    newNode->left = NULL;

    return newNode;
}

void insert(struct Node** root, int newValue)
{
    struct Node* newNode = createNode(newValue);

    if (*root == NULL)
    {
        *root = newNode;
    }
    else
    {
        struct Node* currNode = *root;
        struct Node* prevNode = NULL;
        while (currNode!=NULL)
        {
            prevNode = currNode;

            if (newValue < currNode->value)
            {
                currNode = currNode->left;
                if (currNode == NULL)
                {
                    prevNode->left = newNode;
                }
            }
            else
            {
                currNode = currNode->right;
                if (currNode == NULL)
                {
                    prevNode->right = newNode;
                }
            }
        }
    }
}

void del(struct Node** root, struct Node* n)
{

}


void printTree(struct Node* root, int space)
{
    if (root == NULL)
        return;
    else
    {
        space+=4;

        printTree(root->right, space);

        printf("\n");
        for (int i=4; i<space; ++i)
        {
            printf(" ");
        }
        printf("%d\n", root->value);

        printTree(root->left, space);
    }
}

void debug(struct Node* root)
{
    if (root == NULL)
        return;
    else
    {
        debug(root->left);
        printf("Node: %d\n", root->value);
        debug(root->right);
    }
}

void createTree(struct Node** root, int* arr, int size)
{
    for (int i=0; i<size; ++i)
    {
        insert(root, arr[i]);
    }
}

int main()
{
    struct Node* root = NULL;

   int arr[10] = {1, 4, 8, 83, 0, -29, 58, 12, 100, -12};
   createTree(&root, arr, 10);
   debug(root);

    printTree(root, 0);
}
