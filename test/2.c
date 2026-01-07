#include<stdio.h>
#include<string.h>
int main()
{
    char a[5]={"hello"};
    int i;
    scanf("%s",&a);
    int len=strlen(a);
    for (i=0;i<len/2;i++)
    {
        if (a[i]!=a[len-i-1])
        {
            printf("no");
            break;
        }
        else 
            printf("yes");
    }
    return 0;
}