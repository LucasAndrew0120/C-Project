#include<stdio.h>
#include<string.h>
#include <ctype.h>
char one(char a[100])
{
    int i,len;
    char b='#';
    len=strlen(a);
    for (i = 0; i < len; i++)
    {
        if (a[i]>=0&&a[i]<=9)
        {
            a[i+1]=a[i];
            a[i]='#';
        }
    }
    return a[100];
}
int main()
{
    char c[100],d[100];
    scanf("%s",c[100]);
    d[100]=one(c);
    printf("%s",c[100]);
    return 0;
}