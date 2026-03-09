#include<stdio.h>
#include<math.h>
#include<windows.h>
int main()
{
    SetConsoleOutputCP(65001);
    int i,j,n;
    double num;
    printf("计算交错序列1-2/3+3/5-4/7+5/9-6/11+...的前N项和,请输入N的值:");
    scanf("%d",&n);
    num=0.0;
    for (i=1,j=1;i<n;i++)
    {
        num=num+pow(-1,i)*(i+1)/(j+2);
        j=j+2;
    }
    printf("结果是:%.4lf",num+1);
    return 0;
}