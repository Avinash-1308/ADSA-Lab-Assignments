
#include <stdio.h>
#include <ctype.h>

int numStack[20];
char opStack[20];

int ntop = -1;
int otop = -1;

void pushNum(int x)
{
    numStack[++ntop] = x;
}

int popNum()
{
    return numStack[ntop--];
}

void pushOp(char x)
{
    opStack[++otop] = x;
}

char popOp()
{
    return opStack[otop--];
}

int priority(char x)
{
    if (x == '*' || x == '/')
        return 2;

    if (x == '+' || x == '-')
        return 1;

    return 0;
}

void calculate()
{
    int a, b;
    char op;

    b = popNum();
    a = popNum();
    op = popOp();

    if (op == '+')
        pushNum(a + b);

    else if (op == '-')
        pushNum(a - b);

    else if (op == '*')
        pushNum(a * b);

    else if (op == '/')
        pushNum(a / b);
}

int main()
{
    char infix[20];
    int i = 0;
    int n;

    scanf("%s", infix);

    while (infix[i] != '\0')
    {
        if (isdigit(infix[i]))
        {
            n = 0;

            while (isdigit(infix[i]))
            {
                n = n * 10 + (infix[i] - '0');
                i++;
            }

            pushNum(n);
        }

        else if (infix[i] == '(')
        {
            pushOp(infix[i]);
            i++;
        }

        else if (infix[i] == ')')
        {
            while (opStack[otop] != '(')
                calculate();

            popOp();
            i++;
        }

        else
        {
            while (otop != -1 &&
                   opStack[otop] != '(' &&
                   priority(opStack[otop]) >= priority(infix[i]))
            {
                calculate();
            }

            pushOp(infix[i]);
            i++;
        }
    }

    while (otop != -1)
        calculate();

    printf("%d", popNum());

    return 0;
}

