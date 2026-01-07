#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>  
int main()
{
    int a[3][4],i,j,num1;
    srand(time(NULL));
    printf("数组原内容为:\n");
    for (i=0;i<3;i++)
    {
        for (j=0;j<4;j++)
        {
            num1=rand()%100;
            a[i][j]=num1;
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }
    printf("数组二次方内容为:\n");
    for (i=0;i<3;i++)
    {
        for (j=0;j<4;j++)
        {
            a[i][j]=pow(a[i][j],2);
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }
    printf("二维数组每行的首地址为:\n");
    for (i=0;i<3;i++)
    {
        printf("%p ",a[i][0]);
    }
    printf("\n");
    printf("二维数组每行的首元素地址为:\n");
    for (i=0;i<3;i++)
    {
        printf("%p ",&a[i][0]);
    }
}