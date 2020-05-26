#include <stdio.h>
#define N 4
#define M 3

void andian(int arr[][M])
{
    int isHas = 0;
    for (int i = 0; i < N; i++)
    {
        int colPos = 0;
        for (int j = 1; j < M; j++)
            if (arr[i][j] < arr[i][colPos])
                colPos = j;
        int colMax = arr[i][colPos];

        int isAnDian = 1;
        for (int j = 0; j < N; j++)
            if (arr[j][colPos] > colMax)
                isAnDian = 0;
        if (isAnDian)
        {
            printf("%d ", colMax);
            isHas = 0;
        }
    }
    if (!isHas)
        printf("no\n");
}

int main()
{
    int arr[][M] = {{11, 13, 121}, {407, 72, 88}, {23, 58, 1}, {134, 30, 62}};
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
            printf("%d ", arr[i][j]);
        printf("\n");
    }
    printf("鞍点: ");

    andian(arr);
    return 0;
}