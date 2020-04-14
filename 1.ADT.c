#include <stdio.h>
#include <stdlib.h>

typedef struct Complex
{
    /* data */
    int e1;
    int e2;
} Complex, *ptrComplex;

/* 创建复数 */
void AssignComplex(ptrComplex *z, int v1, int v2)
{
    *z = (ptrComplex)malloc(sizeof(Complex));
    (*z)->e1 = v1;
    (*z)->e2 = v2;
}

/* 复数加法运算 */
void Add(Complex z1, Complex z2, ptrComplex sum)
{
    sum->e1 = z1.e1 + z2.e1;
    sum->e2 = z1.e2 + z2.e2;
}

/* 复数减法运算 */
void Minus(Complex z1, Complex z2, ptrComplex sum)
{
    sum->e1 = z1.e1 - z2.e1;
    sum->e2 = z1.e2 - z2.e2;
}

/* 复数乘法运算 */
void Multiply(Complex z1, Complex z2, ptrComplex sum)
{
    sum->e1 = z1.e1 * z2.e1 - z1.e2 * z2.e2;
    sum->e2 = z1.e2 * z2.e1 + z1.e1 * z2.e2;
}

/* 复数乘法运算 */
void Over(Complex z1, Complex z2, ptrComplex sum)
{
    sum->e1 = (z1.e1 * z2.e1 + z1.e2 * z2.e2) / (z2.e1 * z2.e1 + z2.e2 * z2.e2);
    sum->e2 = (z1.e2 * z2.e1 - z1.e1 * z2.e2) / (z2.e1 * z2.e1 + z2.e2 * z2.e2);
}

/* 删除复数 */
void DestroyComplex(ptrComplex z)
{
    free(z);
}

int main()
{
    ptrComplex z1 = NULL, z2 = NULL;
    Complex res;

    // 创建复数
    AssignComplex(&z1, 7, 4);
    AssignComplex(&z2, 1, 2);

    printf("z1: %d + %di\n", z1->e1, z1->e2);
    printf("z2: %d + %di\n\n", z2->e1, z2->e2);

    // 复数相加
    Add(*z1, *z2, &res);
    printf("z1 + z2 = %d + %di\n", res.e1, res.e2);

    // 复数相减
    Minus(*z1, *z2, &res);
    printf("z1 - z2 = %d + %di\n", res.e1, res.e2);

    // 复数相乘
    Multiply(*z1, *z2, &res);
    printf("z1 * z2 = %d + %di\n", res.e1, res.e2);

    // 复数相除
    Over(*z1, *z2, &res);
    printf("z1 / z2 = %d + %di\n", res.e1, res.e2);

    // 摧毁复数变量
    DestroyComplex(z1);
    DestroyComplex(z2);

    return 0;
}