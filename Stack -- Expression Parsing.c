#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#define MAX_NUM_LENGTH 1000
#define MAX_EXPRESSION_SIZE 1000

struct StackNode
{
    int value;
    struct StackNode* next;
};

struct StackNode* createNode(int newValue)
{
    struct StackNode* newNode = malloc(sizeof(struct StackNode));
    newNode->value = newValue;
    newNode->next = NULL;

    return newNode;
}

void push(struct StackNode** top, int newValue)
{
    struct StackNode* newNode = createNode(newValue);
    newNode->next = *top;
    *top = newNode;
}

int pop(struct StackNode** top)
{
    if (*top==NULL)
        return -1;
    else
    {
        int poppedValue = -1;
        poppedValue = (*top)->value;

        struct StackNode* nextNode = (*top)->next;
        free(*top);
        *top = nextNode;

        return poppedValue;
    }
}

int peek(struct StackNode* top)
{
    if (top==NULL)
        return -1;
    else
        return top->value;
}

void freeStack(struct StackNode** top)
{
    while (*top!=NULL)
    {
        pop(top);
    }
}

bool isNumeric(char x)
{
    return (x>='0' && x<='9');
}

bool isNumericStr(char* str)
{
    if (str[0] == '-')
    {
        return (str[1]>='0' && str[1]<='9');
    }
    else
    {
        return (str[0]>='0' && str[0]<='9');
    }
}

int parseInt(char* str)
{
    int parsed;
    sscanf(str, "%d", &parsed);

    return parsed;
}

int precedenceOf(char op)
{
    //The larger the number, the greater the precedence.
    switch (op)
    {
    case '(':
        return 0;
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
    case '%':
        return 2;
    case '^':
        return 3;
    default:
        printf("Error on parsing operator precedence.\n");
        return -1;
    }
}

int parseOperator(int a, int b, char op)
{
    switch (op)
    {
    case '+':
        return a+b;
    case '-':
        return a-b;
    case '*':
        return a*b;
    case '/':
        if (b==0)
        {
            printf("Error: Division by 0.\n");
            return -1;
        }
        else
            return a/b;
    case '^':
        return pow(a, b);
    case '%':
        return a%b;
    default:
        printf("Error on operator parsing.\n");
        return -1;
    }
}

int parseString(char* inputString, char parsedString_Out[][MAX_NUM_LENGTH])
{
    int i=0, j=0, size=0;

    //While the inputString hasn't ended,
    while (inputString[i]!='\0')
    {
        //ignore spaces,
        if (inputString[i] == ' ')
        {
            while (inputString[i] == ' ')
                ++i;
        }
        //parse numbers,
        else if (isNumeric(inputString[i]))
        {
            while (isNumeric(inputString[i]))
            {
                parsedString_Out[size][j++] = inputString[i++];
            }
            parsedString_Out[size++][j] = '\0';
            j=0;
        }
        //and parse operators;
        else if (inputString[i]!='\0')
        {
            //Special case for unary minus
            if (inputString[i] == '-')
            {
                if (size == 0)
                {
                    parsedString_Out[size][j++] = inputString[i++];
                    continue;
                }

                char x = parsedString_Out[size-1][0];
                char y = parsedString_Out[size-1][1];
                if ((!isNumeric(x) && y == '\0' && x!=')'))
                {
                    parsedString_Out[size][j++] = inputString[i++];
                    continue;
                }
            }

            parsedString_Out[size][j++] = inputString[i++];
            parsedString_Out[size++][j] = '\0';
            j=0;
        }
    }

    return size;
}

int parsePostfix(char parsedString[][MAX_NUM_LENGTH], int size)
{
    struct StackNode* top = NULL;

    for (int i=0; i<size; ++i)
    {
        if (isNumericStr(parsedString[i]))
            push(&top, parseInt(parsedString[i]));
        else
        {
            char op = parsedString[i][0];
            int b = pop(&top);
            int a = pop(&top);

            push(&top, parseOperator(a, b, op));
        }
    }

    int parseResult = peek(top);
    freeStack(&top);

    return parseResult;
}

int parsePrefix(char parsedString[][MAX_NUM_LENGTH], int size)
{
    struct StackNode* top = NULL;

    for (int i=size; i-- > 0;)
    {
        if (isNumericStr(parsedString[i]))
            push(&top, parseInt(parsedString[i]));
        else
        {
            char op = parsedString[i][0];
            int a = pop(&top);
            int b = pop(&top);

            push(&top, parseOperator(a, b, op));
        }
    }

    int parseResult = peek(top);
    freeStack(&top);

    return parseResult;
}

void convertToPostfix(char parsedString_Out[][MAX_NUM_LENGTH], int* size_Out)
{
    //Uses the Shunting-yard algorithm to produce a Postfix result.
    struct StackNode* top = NULL;

    int newSize=0;
    for (int i=0; i<(*size_Out); ++i)
    {
        char c = parsedString_Out[i][0];

        if (isNumericStr(parsedString_Out[i]))
        {
            strcpy(parsedString_Out[newSize++], parsedString_Out[i]);
        }
        else if (c == '(')
        {
            push(&top, '(');
        }
        else if (c == ')')
        {
            while (peek(top)!='(')
            {
                parsedString_Out[newSize][0] = pop(&top);
                parsedString_Out[newSize++][1] = '\0';
            }
            pop(&top);
        }
        else
        {
            while (top!=NULL && precedenceOf(peek(top)) >= precedenceOf(c))
            {
                parsedString_Out[newSize][0] = pop(&top);
                parsedString_Out[newSize++][1] = '\0';
            }
            push(&top, c);
        }
    }

    while (top!=NULL)
    {
        parsedString_Out[newSize][0] = pop(&top);
        parsedString_Out[newSize++][1] = '\0';
    }

    *size_Out = newSize;
}

void debug(char parsedString[MAX_EXPRESSION_SIZE][MAX_NUM_LENGTH], int size)
{
    for (int i=0; i<size; ++i)
    {
        printf("LOC%d : %s\n", i, parsedString[i]);
    }
}

int main()
{
    char inputString[MAX_EXPRESSION_SIZE*MAX_NUM_LENGTH];
    char parsedString[MAX_EXPRESSION_SIZE][MAX_NUM_LENGTH];

    printf("Enter an infix notation equation:\n >> ");
    scanf("%[^\n]", inputString);

    int size = parseString(inputString, parsedString);
    debug(parsedString, size);
    convertToPostfix(parsedString, &size);
     debug(parsedString, size);

    printf("Result: %d\n", parsePostfix(parsedString, size));
}
