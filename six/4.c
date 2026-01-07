#include<stdio.h>
int MyStrCmp(char *sa, char *sb)
{
    while (*sa==*sb&&*sa!='\0')
    {
        sa++;
        sb++;
    }
    if (*sa==*sb)
    {
        return 0;
    }
    else if (*sa>*sb)
    {
        return 1;
    }
    else if (*sa<*sb)
    {
        return -1;
    }
}
int main()
{
    int n;
    char a[100],b[100],*x,*y;
    printf("请输入两组字符串：");
    gets(a);
    gets(b);
    x=a;
    y=b;
    n=MyStrCmp(x,y);
    printf("%d",n);
    return 0;
}