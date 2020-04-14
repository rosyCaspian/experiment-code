#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Row
{
    char *str;
    struct Row *next;
} Row;

typedef struct Page
{
    Row *rowContent;
    int rowNum;
    struct Page *next;
} Page;

typedef struct Editor
{
    Page *pageContent;
    int pageNum;
} Editor;

Page *_newPage(Page *pageContent)
{
    pageContent->next = (Page *)malloc(sizeof(Page));
    pageContent->next->next = NULL;

    return pageContent->next;
}

Row *_newRow(Row *rowContent)
{
    rowContent->next = (Row *)malloc(sizeof(Row));
    rowContent->next->next = NULL;

    return rowContent->next;
}

void _appendRow(Page *pageContent, char *indexStr)
{
    int i;
    Row *tempRowContent = pageContent->rowContent;
    while (tempRowContent->next)
        tempRowContent = tempRowContent->next;

    tempRowContent = _newRow(tempRowContent);
    tempRowContent->str = (char *)malloc(sizeof(char) * (strlen(indexStr) + 1));

    for (i = 0; indexStr[i] != '\0'; i++)
        tempRowContent->str[i] = indexStr[i];
    tempRowContent->str[i] = '\0';

    (pageContent->rowNum)++;
}

void _appendPage(Editor *pEditor)
{
    Page *tempPageContent = pEditor->pageContent;
    while (tempPageContent->next)
        tempPageContent = tempPageContent->next;

    tempPageContent = _newPage(tempPageContent);
    tempPageContent->rowContent = (Row *)malloc(sizeof(Row));
    tempPageContent->rowContent->next = NULL;

    (pEditor->pageNum)++;
}

Editor *initEditor()
{
    Editor *pEditor = (Editor *)malloc(sizeof(Editor));
    pEditor->pageNum = 0;
    pEditor->pageContent = (Page *)malloc(sizeof(Page));
    pEditor->pageContent->next = NULL;

    return pEditor;
}

void appendContent(Editor *pEditor, char *indexStr)
{
    _appendPage(pEditor);
    Page *tempPageContent = pEditor->pageContent->next;
    char tempStr[300];
    int index = 0;

    for (int i = 0; indexStr[i] != '\0'; i++)
    {
        if (indexStr[i] == '\f')
        {
            tempStr[index] = '\0';
            _appendRow(tempPageContent, tempStr);

            _appendPage(pEditor);
            tempPageContent = tempPageContent->next;
            index = 0;
        }
        else if (indexStr[i] == '\n')
        {
            tempStr[index] = '\0';
            _appendRow(tempPageContent, tempStr);
            index = 0;
        }
        else
            tempStr[index++] = indexStr[i];
    }
}

int strIndex(char *dst, char *scr)
{
    int i, j, index = 1;
    for (i = 0; dst[i] != '\0'; i++)
    {
        for (j = 0; (dst[i + j] != '\0') && (scr[j] != '\0'); j++)
            if (dst[i + j] != scr[j])
            {
                index = -1;
                break;
            }
        if ((index != -1) && (scr[j] == '\0'))
            return i;
        index = 1;
    }
    return -1;
}

void search(Editor *pEditor, char *indexStr, int *result)
{
    int pageNum = 0, rowNum = 0, colNum = 0;
    result[0] = -1;

    Page *tempPageContent = pEditor->pageContent->next;
    Row *tempRowContent;

    while (tempPageContent)
    {
        pageNum++;
        tempRowContent = tempPageContent->rowContent->next;
        while (tempRowContent)
        {
            rowNum++;
            colNum = strIndex(tempRowContent->str, indexStr);
            if (colNum != -1)
            {
                result[0] = 1;
                result[1] = pageNum;
                result[2] = rowNum;
                result[3] = colNum + 1;

                return;
            }
            tempRowContent = tempRowContent->next;
        }
        rowNum = 0;
        tempPageContent = tempPageContent->next;
    }
}

void display(Editor *pEditor)
{
    Page *tempPageContent = pEditor->pageContent->next;
    Row *tempRowContent;
    int pageNum = 1, rowNum = 1;

    while (tempPageContent)
    {
        tempRowContent = tempPageContent->rowContent->next;
        while (tempRowContent)
        {
            printf("%d| %s\n", rowNum++, tempRowContent->str);
            tempRowContent = tempRowContent->next;
        }
        printf("第 %d 页\n", pageNum++);
        rowNum = 1;
        tempPageContent = tempPageContent->next;
        printf("\n");
    }
}

void destroy(Editor *pEditor)
{
    Page *tempPageFree, *tempPageContent = pEditor->pageContent->next;
    free(pEditor->pageContent); // 释放头节点
    pEditor->pageContent = NULL;
    Row *tempRowContent, *tempRowFree;

    while (tempPageContent)
    {
        tempRowContent = tempPageContent->rowContent->next;
        free(tempPageContent->rowContent); // 释放头节点
        tempPageContent->rowContent = NULL;
        while (tempRowContent)
        {
            free(tempRowContent->str);
            tempRowContent->str = NULL;
            tempRowFree = tempRowContent->next;
            free(tempRowContent);
            tempRowContent = tempRowFree;
        }
        tempPageFree = tempPageContent->next;
        free(tempPageContent);
        tempPageContent = tempPageFree;
    }
}

int main()
{
    Editor *pEditor = initEditor();
    appendContent(pEditor, "To see a world in a grain of sand,\nAnd a heaven in a wild flower,\nHold infinity in the palm of your hand,\nAnd eternity in an hour.\fMy love is like the grasses.\nHidden in the deep mountains.\nThough its abundance increase,\nThere is none that knows.");
    display(pEditor);

    int result[4];
    char *searchStr1 = "And eternity in an hour";
    search(pEditor, searchStr1, result);
    if (result[0] != -1)
        printf("\'%s\': page %d | row %d | column %d\n", searchStr1, result[1], result[2], result[3]);
    else
        printf("查找无结果!\n");

    char *searchStr2 = "We will meet again.";
    search(pEditor, searchStr2, result);
    if (result[0] != -1)
        printf("\'%s\': page %d | row %d | column %d\n", searchStr2, result[1], result[2], result[3]);
    else
        printf("\'%s\': 查找无结果!\n", searchStr2);

    destroy(pEditor);
    return 0;
}