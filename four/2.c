#include<stdio.h>
int main()
{
    int a,i;
    int score[14];
    int b=0;
    scanf("%d",&a);
    for(i=0;a>0;i++)
    {
        score[i]=a%2;
        a=a/2;
        b++;
    }
    for (i=b-1;i>=0;i--)
    {
        printf("%d",score[i]);
    }
    return 0;
}