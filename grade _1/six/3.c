#include<stdio.h>
int * FindMaxMin1(int a[], int n)
{
    int i,*j,*z;
    static int result[2]; //静态数组
    printf("请输入整数:");
    for (i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
    }
    j=a;
    z=a;
    for (i=0;i<n;i++)
    {
        if (*j>a[i])
        {
            j=&a[i];
        }
        if (*z<a[i])
        {
            z=&a[i];
        }
    }
    result[0] = *j;  // 最大值
    result[1] = *z;  // 最小值
    return result;
}
int main()
{
    int n2;
    int a2[1000];
    int c[2];
    printf("请输入整数个数：");
    scanf("%d",&n2);
    int *result = FindMaxMin1(a2,n2);
    c[0]= result[0];
    c[1]= result[1];
    printf("最大值和最小值分别为:%d %d",c[0],c[1]);
    return 0;
}