#include <stdio.h>
#include <stdlib.h>

typedef struct BinaryTree
{
    char data;
    struct BinaryTree *pLeftChild;
    struct BinaryTree *pMidChild;
    struct BinaryTree *pRightChild;
} BinaryTree;

BinaryTree *initBinaryTree(char data)
{
    BinaryTree *pRoot = (BinaryTree *)malloc(sizeof(BinaryTree));
    pRoot->data = data;
    pRoot->pLeftChild = NULL;
    pRoot->pMidChild = NULL;
    pRoot->pRightChild = NULL;

    return pRoot;
}

BinaryTree *addLeftChild(BinaryTree *pParent, char data)
{
    pParent->pLeftChild = (BinaryTree *)malloc(sizeof(BinaryTree));
    pParent->pLeftChild->data = data;
    pParent->pLeftChild->pLeftChild = NULL;
    pParent->pLeftChild->pMidChild = NULL;
    pParent->pLeftChild->pRightChild = NULL;

    return pParent->pLeftChild;
}

BinaryTree *addMidChild(BinaryTree *pParent, char data)
{
    pParent->pMidChild = (BinaryTree *)malloc(sizeof(BinaryTree));
    pParent->pMidChild->data = data;
    pParent->pMidChild->pLeftChild = NULL;
    pParent->pMidChild->pMidChild = NULL;
    pParent->pMidChild->pRightChild = NULL;

    return pParent->pMidChild;
}

BinaryTree *addRightChild(BinaryTree *pParent, char data)
{
    pParent->pRightChild = (BinaryTree *)malloc(sizeof(BinaryTree));
    pParent->pRightChild->data = data;
    pParent->pRightChild->pLeftChild = NULL;
    pParent->pRightChild->pMidChild = NULL;
    pParent->pRightChild->pRightChild = NULL;

    return pParent->pRightChild;
}

void print(BinaryTree *pRoot, int nlayer)
{
    if (pRoot)
    {
        for (int i = 0; i < nlayer; i++)
            printf(" ");
        printf("%c\n", pRoot->data);
        print(pRoot->pLeftChild, nlayer + 2);
        print(pRoot->pMidChild, nlayer + 2);
        print(pRoot->pRightChild, nlayer + 2);
    }
}

void destory(BinaryTree *pRoot)
{
    if (pRoot)
    {
        destory(pRoot->pLeftChild);
        destory(pRoot->pMidChild);
        destory(pRoot->pRightChild);
        free(pRoot);
        pRoot = NULL;
    }
}

int main()
{
    BinaryTree *pRoot = initBinaryTree('A');
    BinaryTree *pTemp1, *pTemp2;

    pTemp1 = addLeftChild(pRoot, 'B');
    addLeftChild(pTemp1, 'E');
    addRightChild(pTemp1, 'F');

    pTemp1 = addMidChild(pRoot, 'C');
    addMidChild(pTemp1, 'G');

    addRightChild(pRoot, 'D');

    printf("\n");
    print(pRoot, 0);
    printf("\n");

    destory(pRoot);

    return 0;
}