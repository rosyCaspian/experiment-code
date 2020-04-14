#include <stdio.h>
#define N 20

typedef struct Stack
{
    int elements[N];
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

void push(Stack *s, int c)
{
    s->elements[s->len++] = c;
}
void pop(Stack *s, int *x)
{
    (s->len)--;
    *x = s->elements[s->len];
}
void conversion(int n, int t)
{
    Stack S;
    int x;
    init(&S);
    //将n转换为t进制
    while (n > 0)
    {
        x = n % t;
        push(&S, x);
        n /= 10;
    }
    //以下为从栈中依次出栈并输出
    while (!isEmpty(&S))
    {
        pop(&S, &x);
        if (x <= 9)
            printf("%d", x); //小于10的，按数值打印
        else
            printf("%c", 'A' + (x - 10)); //大于10的，按字符打印
    }
}

int main()
{
    printf("十进制数: %d\n十一进制数: ", 100);
    conversion(100, 11);
    return 0;
}