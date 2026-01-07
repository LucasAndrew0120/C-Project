#include<stdio.h>
#include<string.h>
int *max(int *a,int b[10])
{
    int i;
    a=&b[0];
    for (i=1;i<10;i++)
    {
        if (b[i]>*a)
            a=&b[i];
    }
    return a;
}
int *min(int *a,int b[10])
{
    int i;
    a=&b[1];
    for (i=1;i<10;i++)
    {
        if (b[i]<*a)
            a=&b[i];
    }
    return a;
}
int main()
{
    int b[10],i,*x,*y;
    for ( i = 0; i < 10; i++)
    {
        scanf("%d",&b[i]);
    }
    x=max(x,b);
    y=min(y,b);
    printf("max=%d,min=%d",*x,*y);
    return 0;
}
