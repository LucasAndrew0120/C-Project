#include<stdio.h>
#include<stdlib.h>
int main()
{
    printf("请输入一组升序数列(6个数)，并将插入数放在数列最后(第六个数)；");
    int a[6],i,j,key;
    for (i=0;i<6;i++)
    {
        scanf("%d",&a[i]);
    }
    key=a[5];
    for (i=0;key>a[i]&&key<a[i+1];i++)
    {
        
    }
    for (j=5;j>i;j--)
    {
        a[j]=a[j-1];
    }
    a[i+1]=key;
    for (i=0;i<6;i++)
    {
        printf("%d ",a[i]);
    }
    return 0;    
}