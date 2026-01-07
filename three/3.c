#include<stdio.h>
int main()
{
    int a,b,c,d,e;
    printf("请输入四位整数:");
    scanf("%d",&a);
    b=a%10;
    c=a/10%10;
    d=a/100%10;
    e=a/1000%10;
    printf("这四位数倒叙排列为：%d%d%d%d",b,c,d,e);
    getchar();
    return 0;
}