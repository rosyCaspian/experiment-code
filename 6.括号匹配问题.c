#include <stdio.h>
#define N 20

typedef struct Stack
{
    char elements[N];
    int len;
} Stack;

void init(Stack *s)
{
    s->len = 0;
}

int isEmpty(Stack *s)
{
    return s->len == 0;
}

void push(Stack *s, char c)
{
    s->elements[s->len++] = c;
}
void getTop(Stack *s, char *c)
{
    *c = s->elements[(s->len) - 1];
}
void pop(Stack *s)
{
    (s->len)--;
}
int math(char a, char b)
{
    switch (a)
    {
    case '(':
        return b == ')';
    case '[':
        return b == ']';
    case '{':
        return b == '}';
    }
    return 0;
}

void brecketMath(char *str)
{
    Stack s;
    char ch;
    init(&s);
    for (int i = 0; str[i] != '\0'; i++)
    {
        switch (str[i])
        {
        case '(':
        case '[':
        case '{':
            push(&s, str[i]);
            break;
        case ')':
        case ']':
        case '}':
            if (!isEmpty(&s))
            {
                getTop(&s, &ch);
                if (math(ch, str[i]))
                    pop(&s);
                else
                    printf("不匹配\n");
            }
            else
                printf("多余右括号\n");
        }
    }
    if (isEmpty(&s))
        printf("括号匹配\n");
    else
        printf("括号不匹配\n");
}
int main()
{
    char *str1 = "{(x-y)*[(x+3y)/(7x-2y) - 10x]}";
    printf("%s\n", str1);
    brecketMath(str1);
    char *str2 = "{(x-y)*[(x+3y)/(7x-2y - 10x";
    printf("%s\n", str2);
    brecketMath(str2);
    return 0;
}