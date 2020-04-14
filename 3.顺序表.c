#include <stdio.h>
#include <stdlib.h>

#define N 100

typedef struct MyList
{
    int len;
    int cap;
    int *list;
} MyList;

MyList *createData(int cap)
{
    int *arr = (int *)malloc(sizeof(int) * cap);
    MyList *li = (MyList *)malloc(sizeof(MyList));
    li->len = 0;
    li->cap = cap;
    li->list = arr;
    return li;
}

void insertData(MyList *li, int index, int data)
{
    if (index > li->len)
        printf("err: invalid index!\n");
    else
    {
        if (li->len >= li->cap)
        {
            li->cap = li->cap + ((li->cap >> 1) > 1 ? (li->cap >> 1) : 1);
            li->list = (int *)malloc(sizeof(int) * li->cap);
        }
        li->list[index] = data;
        li->len++;
    }
}

void deleteData(MyList *li, int index)
{
    if (index >= li->len)
        printf("err: invalid index!\n");
    else
    {
        for (int i = index; i < li->len - 1; i++)
            li->list[index] = li->list[index + 1];
        li->len--;
    }
}

int searchData(MyList *li, int index)
{
    if (index >= li->len)
        return EOF;
    return li->list[index];
}

void printList(MyList *li)
{
    printf("顺序表信息:\n");
    printf("元素: [ ");
    for (int i = 0; i < li->len; i++)
        printf("%d ", li->list[i]);
    printf("]\n长度: %d\n容量: %d\n", li->len, li->cap);
}

int main()
{
    MyList *li = createData(N);
    printList(li);

    printf("\n插入十个元素\n");
    for (int i = 0; i < 10; i++)
        insertData(li, i, i + 1);
    printList(li);

    printf("\n删除五个元素\n");
    for (int i = 0; i < 5; i++)
        deleteData(li, i);
    printList(li);

    printf("\n查找第3个元素\n");
    int res = searchData(li, 3);
    if (res == EOF)
        printf("查找错误\n");
    else
    {
        printf("元素为: %d", res);
    }

    return 0;
}