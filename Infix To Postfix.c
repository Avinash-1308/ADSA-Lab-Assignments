#include <stdio.h>
#include <ctype.h>

char stack[20];
int top = -1;

void push(char x)
{
    top++;
    stack[top] = x;
}

char pop()
{
    char x = stack[top];
    top--;
    return x;
}

int priority(char x)
{
    if (x == '*' || x == '/')
        return 2;

    if (x == '+' || x == '-')
        return 1;

    return 0;
}

int main()
{
    char infix[20];
    int i;
    char x;

    scanf("%s", infix);

    i = 0;

    while (infix[i] != '\0')
    {
        x = infix[i];

        if (isdigit(x))
        {
            while (isdigit(infix[i]))
            {
                printf("%c", infix[i]);
                i++;
            }
        }

        else if (x == '(')
        {
            push(x);
            i++;
        }

        else if (x == ')')
        {
            while (stack[top] != '(')
            {
                printf("%c", pop());
            }

            pop();
            i++;
        }

        else
        {
            while (top != -1 &&
                   stack[top] != '(' &&
                   priority(stack[top]) >= priority(x))
            {
                printf("%c", pop());
            }

            push(x);
            i++;
        }
    }

    while (top != -1)
    {
        printf("%c", pop());
    }

    return 0;
}