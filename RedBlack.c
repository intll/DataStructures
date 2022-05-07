#include <stdio.h>
#include <stdlib.h>

enum Color
{
    RED,
    BLACK,
};

struct Node
{
    int val;
    Color type;

    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int newVal)
{
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->type = red;
    newNode->val = newVal;
    newNode->right = NULL;
    newNode->left = NULL;

    return newNode;
}

bool isRed(struct Node* n)
{
    return (n!=NULL && n->type == RED) ? true : false;
}

struct Node* leftRotate(struct Node* x)
{
    struct Node* y = x->right;
    x->right = y->left;
    y->left = x;

    return y;
}

struct Node* rightRotate(struct Node* x)
{
    struct Node* y = x->left;
    x->left = y->right;
    y->right = x;

    return y;
}

void Node* flipColors(struct Node* x)
{
    x.type = RED;
    x->left->type = BLACK;
    x->right->type = BLACK;
}


void balance(struct Node* root, struct Node* n)
{
    if (isRed(n->left) && isRed(n->right))
    {
        flipColors(n);
    }

}

void insert(struct Node** root, int newVal)
{
    struct Node** curr = root;

    if (*curr == NULL)
    {
        *curr = createNode(newVal);
        return;
    }
    else if (newVal > (*root)->val)
    {
        insert(&(*curr)->right, newVal);
    }
    else
    {
        insert(&(*curr)->left, newVal);
    }

    *curr = balance(*root, *curr);
}

int main()
{

}
