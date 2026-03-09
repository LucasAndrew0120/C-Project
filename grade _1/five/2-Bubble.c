#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main()
{
    srand(time(NULL));
    int a[20],i,j;
    int temp,max;
    for (i=0;i<20;i++)
    {
        int num=rand()%100;
        a[i]=num;
    }
    for (i=0;i<19;i++)
    for (j=0;j<19-i;j++)
    {
        if(a[j]<a[j+1])
        {
            temp=a[j];
            a[j]=a[j+1];
            a[j+1]=temp;
        }
    }
    for (i=0;i<20;i++)
    {
        printf("%d ",a[i]);
    }
    return 0;
}