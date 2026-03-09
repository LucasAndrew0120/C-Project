#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main()
{
    srand(time(NULL));
    int a[20],i,j;
    int temp,max;
    for ( i = 0; i < 20; i++)
    {
        int num=rand()%100;
        a[i]=num;
    }
    for ( i = 0; i < 19; i++)
    {
        max=i;
        for ( j = i+1; j<20; j++)
        {
            if (a[j]>a[max])
            {
                max=j;
            }
        }
        if (max!=i)
            {
                temp=a[i];
                a[i]=a[max];
                a[max]=temp;
            }   
    }
    int key,low,mid,high,succes,location;
    printf("现在有一个20个数的降序数列,请输入你要查找的数字：");
    scanf("%d",&key);
    low=0,high=19;
    while(low<=high)
    {
        mid=((low+high)/2);
        if(key==a[mid])
        {
            succes=1;
            location=mid;
            break;
        }
        if (key<a[mid])
        {
            high=mid-1;
        }
        else
        {
            low=mid+1;
        }    
    }
    if(succes==1)
        printf("找到了你要找到的数字:%d\n",&key);
    else
        printf("这个数列里没有找到你要找的数字\n");
    printf("数列是:");
    for (i=0;i<20;i++)
    {
        printf("%d ",a[i]);
    }
    return 0;
}