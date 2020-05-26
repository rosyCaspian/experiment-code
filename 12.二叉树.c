#include <stdio.h>
#include <stdlib.h>

typedef struct BinaryTree
{
    char data;
    struct BinaryTree *pLeftChild;
    struct BinaryTree *pRightChild;
} BinaryTree;

BinaryTree *initBinaryTree(char data)
{
    BinaryTree *pRoot = (BinaryTree *)malloc(sizeof(BinaryTree));
    pRoot->data = data;
    pRoot->pLeftChild = NULL;
    pRoot->pRightChild = NULL;

    return pRoot;
}

BinaryTree *addLeftChild(BinaryTree *pParent, char data)
{
    pParent->pLeftChild = (BinaryTree *)malloc(sizeof(BinaryTree));
    pParent->pLeftChild->data = data;
    pParent->pLeftChild->pLeftChild = NULL;
    pParent->pLeftChild->pRightChild = NULL;

    return pParent->pLeftChild;
}

BinaryTree *addRightChild(BinaryTree *pParent, char data)
{
    pParent->pRightChild = (BinaryTree *)malloc(sizeof(BinaryTree));
    pParent->pRightChild->data = data;
    pParent->pRightChild->pLeftChild = NULL;
    pParent->pRightChild->pRightChild = NULL;

    return pParent->pRightChild;
}

// 先序遍历
void printFirst(BinaryTree *pRoot)
{
    if (pRoot)
    {
        printf("%c ", pRoot->data);
        printFirst(pRoot->pLeftChild);
        printFirst(pRoot->pRightChild);
    }
}

// 中序遍历
void printSecond(BinaryTree *pRoot)
{
    if (pRoot)
    {
        printSecond(pRoot->pLeftChild);
        printf("%c ", pRoot->data);
        printSecond(pRoot->pRightChild);
    }
}
// 后序遍历
void printLast(BinaryTree *pRoot)
{
    if (pRoot)
    {
        printLast(pRoot->pLeftChild);
        printLast(pRoot->pRightChild);
        printf("%c ", pRoot->data);
    }
}

void destory(BinaryTree *pRoot)
{
    if (pRoot)
    {
        destory(pRoot->pLeftChild);
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
    addLeftChild(pTemp1, 'C');
    pTemp2 = addRightChild(pTemp1, 'D');
    pTemp1 = addLeftChild(pTemp2, 'E');
    addRightChild(pTemp1, 'G');
    addRightChild(pTemp2, 'F');

    printf("先序遍历: ");
    printFirst(pRoot);
    printf("\n");

    printf("中序遍历: ");
    printSecond(pRoot);
    printf("\n");

    printf("后序遍历: ");
    printLast(pRoot);
    printf("\n");

    destory(pRoot);

    return 0;
}