#include<stdio.h>
int main() 
{
    int a,b,c,t;
    printf("请输入任意三个整数：");
    scanf("%d %d %d",&a,&b,&c);
    if (a>b)
    {
        t=a;
        a=b;
        b=t;
    }
    if (a>c)
    {
        t=a;
        a=c;
        c=t;
    }
    if (b>c)
    {
        t=b;
        b=c;
        c=t;
    }
    printf("%d %d %d\n",a,b,c);
    getchar();
    return 0;
}