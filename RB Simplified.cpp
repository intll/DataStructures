#include <stdio.h>
#include <stdlib.h>

enum Color
{
    BLACK,
    RED
};

struct Node
{
    int val;
    Color color;

    Node* left;
    Node* right;
    Node* parent;
};

Node* root = NULL;

int isRed(Node* n)
{
    return n != NULL && n->color == RED;
}

Node* createNode(int val)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->val = val;
    newNode->color = RED;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;

    return newNode;
}

void setParent(Node* child, Node* parent)
{
    if (child)
    {
        if (parent == NULL)
        {
            root = child;
        }
        child->parent = parent;
    }
}

Node* push(Node* curr, Node* temp)
{
    if (!curr)
    {
        return temp;
    }
    else if (temp->val < curr->val)
    {
        //Curr->left/right will never be NULL, since either it catches a duplicate,
        //or it returns the newNode.
        curr->left = push(curr->left, temp);
        curr->left->parent = curr;
    }
    else if (temp->val > curr->val)
    {
        curr->right = push(curr->right, temp);
        curr->right->parent = curr;
    }

    return curr;
}

Node* rotateLeft(Node* curr)
{
    Node* rightNode = curr->right;
    curr->right = rightNode->left;
    setParent(curr->right, curr);
    setParent(rightNode, curr->parent);

    if (rightNode->parent)
    {
        if (curr == rightNode->parent->left)
            rightNode->parent->left= rightNode;
        else
            rightNode->parent->right = rightNode;
    }

    rightNode->left = curr;
    curr->parent = rightNode;

    return rightNode;
}

Node* rotateRight(Node* curr)
{
    Node* leftNode = curr->left;
    curr->left = leftNode->right;
    setParent(curr->left, curr);
    setParent(leftNode, curr->parent);

    if (leftNode->parent)
    {
        if (curr == leftNode->parent->left)
            leftNode->parent->left = leftNode;
        else
            leftNode->parent->right = leftNode;
    }

    leftNode->right = curr;
    curr->parent = leftNode;

    return leftNode;
}

void flipColors(Node* pNode, Node* gpNode, Node* uNode)
{
    pNode->color = BLACK;
    uNode->color = BLACK;
    gpNode->color = RED;
}

void swapColors(Node* pNode, Node* gpNode)
{
    Color pColor = pNode->color;
    pNode->color = gpNode->color;
    gpNode->color = pColor;
}

void rebalance(Node* curr)
{
    Node* pNode = NULL;
    Node* gpNode = NULL;
    Node* uNode = NULL;
    //The only case where curr->parent is NULL is the root. So no need to check curr->parent!=NULL
    //gpNode also will never be NULL, since when parent is ROOT, parent is never RED.
    while (curr!=root && curr->color == RED && curr->parent->color == RED)
    {
        pNode = curr->parent;
        gpNode = pNode->parent;

        if (pNode == gpNode->left) //Case where its on the left of grandparent
        {
            uNode = gpNode->right; //Find uncle node
            if (isRed(uNode)) //If uncle is red
            {
                flipColors(pNode, gpNode, uNode); //Just flip the colors
                curr = gpNode;
            }
            else //If uncle is black
            {
                if (curr != pNode->left) //Else if the red nodes do not align, double rotate
                {
                    pNode = rotateLeft(pNode);
                }
                rotateRight(gpNode);
                swapColors(pNode, gpNode);
                curr = pNode; //pNode now takes place of gpNode
            }
        }
        else //Exactly the same as above, just this time its on the left of the grandparent.
        {
            uNode = gpNode->left;
            if (isRed(uNode))
            {
                flipColors(pNode, gpNode, uNode);
                curr = gpNode;
            }
            else
            {
                if (curr != pNode->right)
                {
                    pNode = rotateRight(pNode);
                }
                rotateLeft(gpNode);
                swapColors(pNode, gpNode);
                curr = gpNode; //pNode now takes place of gpNode
            }
        }
    }
    root->color = BLACK;
}

void pushData(int val)
{
    Node* temp = createNode(val);
    root = push(root, temp);
    if (temp->parent || root == temp) //If insert is successful, rebalance
        rebalance(temp);
    else
        free(temp); //Make sure no memory leak occurs when a duplicate key exists
}

void inorder(Node* curr)
{
    if (curr)
    {
        inorder(curr->left);
        printf("%d ", curr->val);
        inorder(curr->right);
    }
}

int main()
{
    int arr[10] = {41, 22, 5, 51, 48, 29, 18, 21, 45, 3};

    for (int i=0; i<10; ++i)
    {
        pushData(arr[i]);
    }

    printf("Inorder Traversal of Created Tree:\n");
    inorder(root);
    printf("\n----------------------------------\n");
}





















