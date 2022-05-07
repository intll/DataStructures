#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int val;

    int height;
    struct Node* left;
    struct Node* right;
};

int max(int a, int b)
{
    return (a>b) ? a : b;
}

int height(struct Node* n)
{
    return n == NULL ? -1 : n->height;
}

int balanceFactor(struct Node* n)
{
    return (height(n->right) - height(n->left));
}

void updateHeight(struct Node* n)
{
    n->height = max(height(n->left), height(n->right))+1;
}

struct Node* createNode(int newVal)
{
    struct Node* newNode = malloc(sizeof(struct Node));

    newNode->val = newVal;
    newNode->height= 0;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

struct Node* leftRotate(struct Node* x)
{
    struct Node* y = x->right;
    x->right = y->left;
    y->left = x;

    updateHeight(x);
    updateHeight(y);

    return y;
}

struct Node* rightRotate(struct Node* x)
{
    struct Node* y = x->left;
    x->left = y->right;
    y->right = x;

    updateHeight(x);
    updateHeight(y);

    return y;
}

struct Node* balance(struct Node* x)
{
    if (x==NULL)
        return NULL;
    else if (balanceFactor(x) < -1)
    {
        if (balanceFactor(x->left) == 1)
            x->left = leftRotate(x->left);

        x = rightRotate(x);
    }
    else if (balanceFactor(x) > 1)
    {
        if (balanceFactor(x->right) == -1)
            x->right = rightRotate(x->right);

        x = leftRotate(x);
    }

    updateHeight(x);
    return x;
}

void insert(struct Node** root, int newVal)
{
    if (*root == NULL)
    {
        *root = createNode(newVal);
        return;
    }
    else if (newVal > (*root)->val)
    {
        insert(&(*root)->right, newVal);
    }
    else
    {
        insert(&(*root)->left, newVal);
    }

    *root = balance(*root);
}

struct Node* minNode(struct Node* root)
{
    while (root->left!=NULL)
    {
        root = root->left;
    }

    return root;
}

void del(struct Node** root, int key)
{
    if (*root == NULL)
        return;
    else if (key < (*root)->val)
    {
        del(&(*root)->left, key);
    }
    else if(key > (*root)->val)
    {
        del(&(*root)->right, key);
    }
    else
    {
        struct Node* n = *root;

        if (n->left == NULL)
        {
            *root = n->right;
            free(n);
        }
        else if (n->right == NULL)
        {
            *root = n->left;
            free(n);
        }
        else
        {
            struct Node* min = minNode((*root)->right);
            (*root)->val = min->val;
            del(&(*root)->right, min->val);
        }
    }

    *root = balance(*root);
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
        printf("%d\n", root->val);

        printTree(root->left, space);
    }
}

int main()
{
    struct Node* root = NULL;

    for (int i=0; i<50; ++i)
    {
        insert(&root, i);
    }

    del(&root, 31);
    printTree(root, 0);
}
