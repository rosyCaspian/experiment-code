#include <stdio.h>
#define N 100

typedef struct Stack
{
    char elements[N];
    int len;
} Stack;

void init(Stack *s)
{
    s->len = 0;
}

int len(Stack *s)
{
    return s->len;
}

void push(Stack *s, char c)
{
    s->elements[s->len++] = c;
}
void getTop(Stack *s, char *c)
{
    *c = s->elements[(s->len) - 1];
}
void pop(Stack *s, char *c)
{
    (s->len)--;
    *c = s->elements[s->len];
}

char convertNumber(Stack *s)
{
    char n = 1, number = 0;
    char c;
    while (s->len > 0)
    {
        pop(s, &c);
        number += ((c - 48) * n);
        n *= 10;
    }
    return number;
}

int level(char c)
{
    switch (c)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '(':
    case ')':
        return 3;
    }
    return -1;
}

char operation(char a, char b, char operator)
{
    switch (operator)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    }
    return -1;
}

char expEvaluation(char *str)
{
    Stack number, operator, temp;
    char a, b, c;
    init(&number);
    init(&operator);
    init(&temp);

    for (int i = 0; str[i] != '\0'; i++)
    {
        // number
        if ((str[i] >= '0') && (str[i] <= '9'))
        {
            push(&temp, str[i]);
            if ((str[i + 1] < '0') || (str[i + 1] > '9'))
                push(&number, convertNumber(&temp));
            continue;
        }

        // operator
        switch (str[i])
        {
        case '+':
        case '-':
        case '*':
        case '/':
        case '(':
            if ((len(&operator) > 0) && (len(&number) >= 2))
            {
                getTop(&operator, &c);
                if ((level(str[i]) <= level(c)) && (c != '('))
                {
                    pop(&number, &a);
                    pop(&number, &b);
                    pop(&operator, &c);
                    push(&number, operation(b, a, c));
                }
            }
            push(&operator, str[i]);
            break;
        // 优先处理
        case ')':
            pop(&operator, &c);
            while (c != '(')
            {
                pop(&number, &a);
                pop(&number, &b);
                push(&number, operation(b, a, c));
                pop(&operator, &c);
            }
        }
    }
    while (len(&number) >= 2)
    {
        pop(&number, &a);
        pop(&number, &b);
        pop(&operator, &c);
        push(&number, operation(b, a, c));
    }
    getTop(&number, &c);
    return c;
}

int main()
{
    char *str = "((3+2)/(3-2)*(1+3*2)-6)*2";
    printf("%s = %d\n", str, expEvaluation(str));
    return 0;
}