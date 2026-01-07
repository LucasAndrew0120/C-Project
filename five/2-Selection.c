#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main()
{
    srand(time(NULL));
    int a[20],i,j;
    int b,temp,c,max;
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
    for (i=0;i<20;i++)
    {
        printf("%d ",a[i]);
    }
    return 0;
    getchar();
}