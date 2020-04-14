#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define N 100

int bubble(int a[], int length)
{
    int i = 0, j, temp;
    int change;
    int count = 0;
    do
    {
        change = 0;
        for (j = 1; j < length - i; j++)
        {
            count++;
            if (a[j] > a[j + 1])
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
                change = 1;
            }
        }
        i = i + 1;
    } while (i < length || change == 1);

    return count;
}

char *TimeComplexity(int (*func)())
{
    int a1[N];
    int a2[N * N];
    int count1, count2;
    char *res = (char *)malloc(sizeof(char) * 20);
    srand(1);

    for (int i = 0; i < N; i++)
        a1[i] = rand() % N;
    for (int i = 0; i < N; i++)
        a2[i] = rand() % N * N;
    count1 = func(a1, N);
    count2 = func(a2, N * N);

    if (count1 == count2)
        strcpy(res, "O(1)");
    else if (count1 <= N * N * N * 10 && count1 > N * N * N / 10)
        strcpy(res, "O(n³)");
    else if (count1 > N * N / 10)
        strcpy(res, "O(n²)");
    else
        strcpy(res, "O(n)");

    return res;
}

char *SpaceComplexity(int (*func)())
{
    char *res = (char *)malloc(sizeof(char) * 20);
    strcpy(res, "O(1)");

    return res;
}

int main()
{
    char *res1 = TimeComplexity(bubble);
    printf("时间复杂度: %s\n", res1);

    char *res2 = SpaceComplexity(bubble);
    printf("空间复杂度: %s", res2);

    return 0;
}