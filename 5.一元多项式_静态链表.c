#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct
{
    int cof;
    int exp;
} Node;

typedef struct
{
    Node data;
    int cur;
} StaticList;

StaticList *make(int n)
{
    StaticList *list = (StaticList *)malloc(sizeof(StaticList) * n);

    // 置空链表
    for (int i = 0; i < n - 1; i++)
        list[i].cur = i + 1;
    list[n - 1].cur = 0;

    return list;
}

int len(StaticList *list, int a)
{
    int n = 0;
    while (a)
    {
        a = list[a].cur;
        n++;
    }
    return n;
}

void sortByExp(StaticList *list, int a)
{
    StaticList *pNow, *pNext;
    int n = len(list, a);

    for (int i = 0; i < n; i++)
    {
        pNow = &list[a];
        pNext = &list[pNow->cur];
        for (int j = 0; j < n - i - 1; j++)
        {
            if (pNow->data.exp > pNext->data.exp)
            {
                Node temp = {pNow->data.cof,
                             pNow->data.exp};
                pNow->data.cof = pNext->data.cof;
                pNow->data.exp = pNext->data.exp;
                pNext->data.cof = temp.cof;
                pNext->data.exp = temp.exp;
            }
            pNow = &list[pNow->cur];
            pNext = &list[pNext->cur];
        }
    }
}

int isSameExp(StaticList *list, int a, Node data)
{
    while (a)
    {
        if (list[a].data.exp == data.exp)
        {
            list[a].data.cof += data.cof;
            return 1;
        }
        a = list[a].cur;
    }
    return 0;
}

void spaceProtect(StaticList **list, int a)
{
    // 空间已满
    if ((*list)[0].cur == 0)
    {
        int oldlen = len(*list, a) + 1;
        int newlen = oldlen + ((oldlen >> 1) > 1 ? (oldlen >> 1) : 1);
        StaticList *newList = make(newlen);
        memcpy(newList, *list, sizeof(StaticList) * oldlen);
        if (*list)
            free(*list);
        (*list) = newList;
        (*list)[0].cur = oldlen;
    }
}

void appendData(StaticList **list, int *a, Node data)
{
    // 确保有足够的空间
    spaceProtect(list, *a);
    if (!isSameExp((*list), *a, data))
    {
        // 获取当前需增添的元素的索引
        int nowIndex = (*list)[0].cur;
        // 空闲空间 -1
        (*list)[0].cur = (*list)[(*list)[0].cur].cur;

        // 增添元素 (头插法)
        (*list)[nowIndex].data.cof = data.cof;
        (*list)[nowIndex].data.exp = data.exp;
        (*list)[nowIndex].cur = *a;
        *a = nowIndex;
    }
}

void insertData(StaticList **list, int *a, int index, Node data)
{
    int listlen = len(*list, *a);
    if (index <= listlen)
    {
        if (!isSameExp((*list), *a, data))
        {
            // 确保有足够的空间
            spaceProtect(list, *a);
            int temp = *a;

            // 空闲空间 -1
            int insertIndex = (*list)[0].cur;
            (*list)[0].cur = (*list)[insertIndex].cur;
            (*list)[insertIndex].data.cof = data.cof;
            (*list)[insertIndex].data.exp = data.exp;

            // 首节点
            if (index == 1)
            {
                (*list)[insertIndex].cur = *a;
                *a = insertIndex;
            }
            else
            {
                for (int i = 0; i < index - 1; i++)
                    temp = (*list)[temp].cur;

                (*list)[insertIndex].cur = (*list)[temp].cur;
                (*list)[temp].cur = insertIndex;
            }
        }
    }
}

void deleteData(StaticList *list, int *a, int index)
{
    int temp = *a;
    int listlen = len(list, *a);

    // 首节点
    if (index == 1)
    {
        // 已用链表指针 -1
        *a = list[*a].cur;
        // 未用链表指针 +1
        list[temp].cur = list[0].cur;
        list[0].cur = temp;
    }
    else if (index <= listlen)
    {
        for (int i = 0; i < index - 1; i++)
            temp = list[temp].cur;

        int temp2 = list[temp].cur;
        list[temp].cur = list[list[temp].cur].cur;
        // 未用链表指针 +1
        list[temp2].cur = list[0].cur;
        list[0].cur = index;
    }
}
void printList(StaticList *list, int a)
{
    if (a != 0)
    {
        sortByExp(list, a);
        printf("F(x) = ");
        printf("%dx^(%d) ", list[a].data.cof, list[a].data.exp);
        a = list[a].cur;

        while (a)
        {
            if (list[a].data.cof > 0)
                printf("+%dx^(%d) ", list[a].data.cof, list[a].data.exp);
            else if (list[a].data.cof < 0)
                printf("%dx^(%d) ", list[a].data.cof, list[a].data.exp);
            a = list[a].cur;
        }
        printf("\n");
    }
    else
    {
        printf("空链表!\n");
    }
}
void combine(StaticList **list1, StaticList *list2, int *a1, int *a2)
{
    int list2_len = len(list2, *a2);
    for (int i = 0; i < list2_len; i++)
    {
        appendData(list1, a1, list2[*a2].data);
        deleteData(list2, a2, 1);
    }
}

void Derivative(StaticList *list, int a)
{
    int i = 1;
    int expDer, cofDer;
    while (a)
    {
        if (((expDer = (list[a].data.exp - 1)) != 0) && ((cofDer = (list[a].data.cof * expDer)) != 0))
        {
            list[a].data.exp = expDer;
            list[a].data.cof = cofDer;
        }
        else
            deleteData(list, &a, i);
        a = list[a].cur;
        i++;
    }
}

int main()
{
    // 设置随机种子
    srand(time(NULL));
    StaticList *list1, *list2;
    // 模拟指向已使用空间的链表指针
    int a1 = 0;
    int a2 = 0;
    // 准备数据
    Node data1[3];
    Node data2[3];
    for (int i = 0; i < 3; i++)
    {
        data1[i].cof = rand() % 100 + 2;
        data1[i].exp = rand() % 100 + 2;
        data2[i].cof = rand() % 100 + 2;
        data2[i].exp = rand() % 100 + 2;
    }
    // 初始化静态链表，先分配10个单元空间
    list1 = make(5);
    list2 = make(5);

    // 增添数据
    for (int i = 0; i < 3; i++)
    {
        appendData(&list1, &a1, data1[i]);
        appendData(&list2, &a2, data2[i]);
    }
    printf("函数: ");
    printList(list1, a1);

    // 合并两个一元多项式
    printf("derivative: ");
    Derivative(list1, a1);
    printList(list1, a1);
    return 0;
}