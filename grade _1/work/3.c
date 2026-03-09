#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
void num(int n,int a[100][100])
{
    int i,j;
    for (i=0;i<n;i++)
    {
        for (j=0;j<n;j++)
        {
            a[i][j]=rand()%101;
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }
}
int main()
{
    int i,n,j;
    int *b,*c;
    int a[100][100];
    srand((unsigned int)time(NULL));
    printf("请输入n阶方阵的n值(n<100):\n");
    scanf("%d",&n);
    printf("随机n阶方阵为:\n");
    num(n,a);
    b=&a[0][0];
    c=&a[0][0];
    for (i=0;i<n;i++)
    {
        if (*b<a[0][i+1])
            b=&a[0][i+1];
        if (*c>a[i+1][0])
            c=&a[i+1][0];
        if (b==c)
            printf("%d",*b);
    }
    if  (b!=c)
        printf("这个n阶矩阵没有鞍点!");
    return 0;
}