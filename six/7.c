#include<stdio.h>
void factorial(int n,int a[])
{
    int i,num;
    num=1;
    for (i=0;i<n;i++)
    {
        num=num*(i+1);
        a[i]=num;
    }
}
int total(int n,int a[])
{
    int num,i;
    num=0;
    printf("计算公式1!+2!+3!+…+n!，请输入n的值:");
    scanf("%d",&n);
    factorial(n,a);
    for(i=0;i<n;i++)
    {
        num=num+a[i];
    }
    return num;
}
int main()
{
    int n;
    int a[100];
    int num=total(n,a);
    printf("公式结果为:%d",num);
    return 0;
}