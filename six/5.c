#include<stdio.h>
void sort(int array[],int n)
{
    int i,temp,min,j;
    min=0;
    for (i=0;i<n-1;i++)
    {
        min=i;
        for (j=i+1;j<n;j++)
        {
            if(array[j]<array[min])
            {
                min=j;
            }
        }
        if (min!=i)
        {
            temp=array[i];
            array[i]=array[min];
            array[min]=temp;
        }
    }
}
int main()
{
    int i,n,a[10000];
    printf("你要输入几个整数？\n");
    scanf("%d",&n);
    printf("请输入整数：");
    for ( i = 0; i < n; i++)
    {
        scanf("%d",&a[i]);
    }
    sort(a,n);
    for (i=0;i<n;i++)
    {
        printf("%d ",a[i]);
    }
    return 0;
}