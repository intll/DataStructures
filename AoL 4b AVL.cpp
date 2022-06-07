#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int val;
    int height;
    Node* left;
    Node* right;
};

int max(int a, int b)
{
    return a > b ? a : b;
}

int getHeight(Node* n)
{
    return n == NULL ? 0 : n->height;
}

int getBalance(Node* n)
{
    ///Using the formula RIGHT-LEFT for the Balance Factor
    return n == NULL ? 0 : getHeight(n->right)-getHeight(n->left);
}

void updateHeight(Node* n)
{
    if (n!=NULL)
    {
        n->height = 1 + max(getHeight(n->right), getHeight(n->left));
    }
}

Node* leftRotate(Node* n)
{
    Node* rightNode = n->right;
    n->right = rightNode->left;
    rightNode->left = n;

    updateHeight(n);
    updateHeight(rightNode);
    return rightNode;
}

Node* rightRotate(Node* n)
{
    Node* leftNode= n->left;
    n->left = leftNode->right;
    leftNode->right = n;

    updateHeight(n);
    updateHeight(leftNode);
    return leftNode;
}

Node* createNode(int val)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->val = val;
    newNode->height = 1;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

Node* getMin(Node* curr)
{
    curr = curr->right;
    while (curr->left!=NULL)
        curr = curr->left;

    return curr;
}

Node* rebalance(Node* curr)
{
    if (getBalance(curr) < -1) //Node is left heavy, either LL or LR case
    {
        if (getBalance(curr->left) >= 1) //Node's left child is of opposite balance: LR case, left rotate first
            curr->left = leftRotate(curr->left);

        return rightRotate(curr); //Either LL or LR will do a right rotate at the end
    }
    else if (getBalance(curr) > 1) // Node is right heavy, either RR or RL case
    {
        if (getBalance(curr->right) <= -1) //Node's right child is of opposite balance: RL case, right rotate first
            curr->right = rightRotate(curr->right);

        return leftRotate(curr); //Either RR or RL will do a left rotate at the end
    }

    updateHeight(curr);
    return curr;
}

Node* push(Node* curr, int val)
{
    if (!curr)
    {
        return createNode(val);
    }
    else if (val < curr->val)
        curr->left = push(curr->left, val);
    else if (val > curr->val)
        curr->right = push(curr->right, val);
    else //Assuming duplicate keys not allowed.
        return curr;

    //Rebalance the tree recursively
    return rebalance(curr);
}

Node* pop(Node* curr, int val, int suppressMessages)
{
    if (!curr)
    {
        printf("Data not found\n");
        return curr;
    }
    else if (val < curr->val)
        curr->left = pop(curr->left, val, suppressMessages);
    else if (val > curr->val)
        curr->right = pop(curr->right, val, suppressMessages);
    else
    {
        if (!suppressMessages)
        {
            printf("Data Found\n");
            printf("Value %d was deleted\n", curr->val);
        }

        //Note that you don't need to check the condition when both children are NULL, this IF will set curr as NULL,
        //since curr->LEFT = NULL when both children are NULL.

        if (curr->right == NULL) //Has right child only or both children are NULL
        {
            Node* temp = curr->left;
            free(curr);
            curr = temp;
        }
        else if (curr->left == NULL) //Has left child only
        {
            Node* temp = curr->right;
            free(curr);
            curr = temp;
        }
        else //Has both child
        {
            Node* minNode = getMin(curr);
            curr->val = minNode->val;
            curr->right = pop(curr->right, minNode->val, 1); //Suppress deletion messages so it doesn't print again
        }
    }

    return rebalance(curr);
}

void preorder(Node* curr)
{
    if (curr)
    {
        printf(" %d", curr->val);
        preorder(curr->left);
        preorder(curr->right);
    }
}

void inorder(Node* curr)
{
    if (curr)
    {
        inorder(curr->left);
        printf(" %d", curr->val);
        inorder(curr->right);
    }
}

void postorder(Node* curr)
{
    if (curr)
    {
        postorder(curr->left);
        postorder(curr->right);
        printf(" %d", curr->val);
    }
}

void print(Node* root)
{
    printf("Preorder:");
    preorder(root);
    putchar('\n');

    printf("Inorder:");
    inorder(root);
    putchar('\n');

    printf("Postorder:");
    postorder(root);
    putchar('\n');
}

int inputData()
{
    int c=0;
    scanf("%d", &c);
    fflush(stdin);

    return c;
}

int main()
{
    Node* root = NULL;
    while (true)
    {
        system("CLS");
        printf("1. Insertion\n");
        printf("2. Deletion\n");
        printf("3. Traversal\n");
        printf("4. Exit\n");
        printf("Choose:\n");

        int c=0;
        scanf("%d", &c);
        fflush(stdin);

        switch (c)
        {
        case 1:
            printf("Insert: ");
            root = push(root, inputData());
            printf("Value inserted\n");
            system("PAUSE");
            break;
        case 2:
            printf("Delete: ");
            root = pop(root, inputData(), 0);
            system("PAUSE");
            break;
        case 3:
            print(root);
            system("PAUSE");
            break;
        case 4:
            printf("Thank you\n");
            return 0;
        default:
            break;
        }
    }
}
