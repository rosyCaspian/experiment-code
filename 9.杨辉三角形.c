#include <stdio.h>

#define MAXSIZE 30

void YangHuiTriangle(int n)
{
    int queue[MAXSIZE];
    int front, rear, num;
    front = rear = 0;

    queue[0] = 1;
    rear = (rear + 1) % MAXSIZE;

    for (int i = 0; i < n; i++)
    {
        queue[rear] = 1;
        rear = (rear + 1) % MAXSIZE;
        num = i;

        for (int j = 0; j < i + 1; j++)
        {
            printf("%d ", queue[front]);
            if (num > 0)
            {
                queue[rear] = queue[front] + queue[(front + 1) % MAXSIZE];
                rear = (rear + 1) % MAXSIZE;
                num--;
            }
            front = (front + 1) % MAXSIZE;
        }
        printf("\n");
        queue[rear] = 1;
        rear = (rear + 1) % MAXSIZE;
    }
}

int main()
{
    YangHuiTriangle(7);

    return 0;
}