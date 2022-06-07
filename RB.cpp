#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum Color
{
    RED,
    BLACK
};

struct Node
{
    int val;
    Color color;

    //0 is left, 1 is right
    Node* link[2];
};

//Global root
Node* root = NULL;

Node* createNode(int val)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->val = val;
    newNode->color = RED;
    newNode->link[0] = NULL;
    newNode->link[1] = NULL;

    return newNode;
}

int isRed(Node* curr)
{
    return curr != NULL && (curr->color == RED);
}


//Using array manipulation, the left and right rotates
//can be concatenated as one. Since it always
//takes the opposite node, using !loc will give the
//opposite node. Remember that loc is the opposite
Node* singleRotate(Node* curr, int loc)
{
    Node* x = curr->link[!loc];

    curr->link[!loc] = x->link[loc];
    x->link[loc] = curr;

    curr->color = RED;
    x->color = BLACK;

    return x;
}

Node* doubleRotate(Node* curr, int loc)
{
    curr->link[!loc] = singleRotate(curr->link[!loc], !loc);
    return singleRotate(curr, loc);
}

Node* rebalance(Node* curr, int loc)
{
    //If the node we are checking is red
    if (isRed(curr->link[loc]))
    {
        //Case where uncle is also red
        if (isRed(curr->link[!loc]))
        {
            //Recolor
            curr->color = RED;
            curr->link[0]->color = BLACK;
            curr->link[1]->color = BLACK;
        }
        else
        {
            //If uncle is not red
            //And the red nodes align, rotate it
            if (isRed(curr->link[loc]->link[loc]))
            {
                curr = singleRotate(curr, !loc);
            } //If the red nodes do not align, do a double rotation
            else if (isRed(curr->link[loc]->link[!loc]))
            {
                curr = doubleRotate(curr, !loc);
            }
        }
    }

    return curr;
}

Node* push(Node* curr, int val)
{
    if (!curr)
    {
        curr = createNode(val);
    }
    else if (curr->val != val)
    {
        //This will give 0 if val is located left, and 1 if its located right
        //Exactly as how we defined link[0] and link[1] as.
        int loc = val > curr->val;
        curr->link[loc] = push(curr->link[loc], val);

        curr = rebalance(curr, loc);
    }

    return curr;
}

void pushData(int val)
{
    root = push(root, val);
    root->color = BLACK;
}

void inorder(Node* curr)
{
    if (!curr)
        return;
    else
    {
        printf("%d ", curr->val);
        inorder(curr->link[0]);
        inorder(curr->link[1]);
    }
}

int test(Node* root)
{
    int lh, rh;

    if (root == NULL)
    {
        return 1;
    }
    else
    {
        Node *ln = root->link[0];
        Node *rn = root->link[1];

        /* Consecutive red links */
        if (isRed(root))
        {
            if (isRed(ln) || isRed(rn))
            {
                puts("Red violation");
                return 0;
            }
        }

        lh = test(ln);
        rh = test(rn);

        /* Invalid binary search tree */
        if ((ln != NULL && ln->val >= root->val) || (rn != NULL && rn->val <= root->val))
        {
            puts("Binary tree violation");
            return 0;
        }

        /* Black height mismatch */
        if (lh != 0 && rh != 0 && lh != rh)
        {
            puts("Black violation");
            return 0;
        }

        /* Only count black links */
        if (lh != 0 && rh != 0)
        {
            return isRed(root) ? lh : lh + 1;
        }
        else
        {
            return 0;
        }
    }
}

int main()
{
    srand(time(NULL));

    for (int i=0; i<20000; ++i)
    {
        printf("test %d\n", i);
        pushData(rand()%20000);
        if (!test(root))
        {
            printf("ERROR! Aborting...\n");
            break;
        }
    }

    inorder(root);

    printf("Test cases passed.\n");
    system("PAUSE");
}
