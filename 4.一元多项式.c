#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int cof;
    int exp;
} Node;

typedef struct MyList
{
    Node data;
    struct MyList *pNext;
} MyList, *ptrMyList;

ptrMyList createList()
{
    ptrMyList pHead = (ptrMyList)malloc(sizeof(MyList));

    pHead->data.cof = 0;
    pHead->data.exp = 0;
    pHead->pNext = NULL;

    return pHead;
}

void sortByExp(ptrMyList pHead)
{
    ptrMyList pTemp, pTempLast, pNow, pLast;
    ptrMyList pUse = pHead;
    int n = 0;
    while (pUse->pNext)
    {
        pUse = pUse->pNext;
        n++;
    }

    for (int i = 0; i < n; i++)
    {
        pLast = pHead;
        pNow = pHead->pNext;
        for (int j = 0; j < n - i - 1; j++)
        {
            if (pNow->data.exp > pNow->pNext->data.exp)
            {
                ptrMyList pT = pNow;
                pLast->pNext = pNow->pNext;
                pT->pNext = pLast->pNext->pNext;
                pLast->pNext->pNext = pT;
            }
            else
                pNow = pNow->pNext;
            pLast = pLast->pNext;
        }
    }
}

void printList(ptrMyList pHead)
{
    ptrMyList pTemp = pHead->pNext;

    printf("F(x) = ");
    printf("%dx^(%d) ", pTemp->data.cof, pTemp->data.exp);
    pTemp = pTemp->pNext;

    while (pTemp)
    {
        if (pTemp->data.cof > 0)
            printf("+%dx^(%d) ", pTemp->data.cof, pTemp->data.exp);
        else if (pTemp->data.cof < 0)
            printf("%dx^(%d) ", pTemp->data.cof, pTemp->data.exp);
        pTemp = pTemp->pNext;
    }
}

void appendData(ptrMyList pHead, Node data)
{
    int isSameExp = 0;

    ptrMyList pTemp = pHead;

    while (pTemp->pNext)
    {
        if (data.exp == pTemp->pNext->data.exp)
        {
            pTemp->pNext->data.cof += data.cof;
            isSameExp = 1;
            break;
        }
        pTemp = pTemp->pNext;
    }
    if (!isSameExp)
    {
        ptrMyList pData = (ptrMyList)malloc(sizeof(MyList));
        pData->data.cof = data.cof;
        pData->data.exp = data.exp;
        pData->pNext = NULL;

        pTemp = pHead;
        while (pTemp->pNext)
            pTemp = pTemp->pNext;
        pTemp->pNext = pData;
    }

    sortByExp(pHead);
}

void combine(ptrMyList pFirst, ptrMyList pSecond, int isAdd)
{
    ptrMyList pTemp1 = pFirst;
    ptrMyList pTemp2 = pSecond;
    ptrMyList pLast = pFirst;
    while (pLast->pNext)
        pLast = pLast->pNext;

    int isHasSameExp;

    while (pTemp2->pNext)
    {
        pTemp1 = pFirst;
        isHasSameExp = 0;

        while (pTemp1->pNext)
        {
            if (pTemp2->pNext->data.exp == pTemp1->pNext->data.exp)
            {
                if (isAdd == 1)
                    pTemp1->pNext->data.cof += pTemp2->pNext->data.cof;
                else
                    pTemp1->pNext->data.cof -= pTemp2->pNext->data.cof;

                if (pTemp1->pNext->data.cof == 0)
                {
                    free(pTemp1->pNext);
                    pTemp1->pNext = pTemp1->pNext->pNext;
                }
                isHasSameExp = 1;
                break;
            }
            pTemp1 = pTemp1->pNext;
        }

        if (!isHasSameExp)
        {
            pLast->pNext = pTemp2->pNext;
            pTemp2->pNext = pTemp2->pNext->pNext;
            pLast->pNext->pNext = NULL;
            pLast = pLast->pNext;
            continue;
        }

        pTemp2 = pTemp2->pNext;
    }

    sortByExp(pFirst);
}

int main()
{
    ptrMyList pHead1 = createList();
    Node data1[6] = {{3, 13}, {-5, 11}, {7, 8}, {8, 2}, {7, 2}, {10, 11}};

    for (int i = 0; i < 6; i++)
        appendData(pHead1, data1[i]);

    printf("函数一:\n");
    printList(pHead1);

    ptrMyList pHead2 = createList();
    Node data2[5] = {{2, 11}, {-3, 21}, {6, 13}, {3, 8}, {2, 17}};

    for (int i = 0; i < 5; i++)
        appendData(pHead2, data2[i]);

    printf("\n函数二:\n");
    printList(pHead2);

    printf("\n\n函数一 函数二 合并:\n");
    combine(pHead1, pHead2, -1);
    printList(pHead1);

    return 0;
}