#include<stdio.h>
#include <string.h>
int main()
{
    char a[49];
    int b=0,c=0,d=0,f=0,e=0;
    fgets(a, sizeof(a), stdin);
    int n=0;
    int length=strlen(a);
    for (int i = 0; i < length; i++,n++)
    {
        if (a[i]>='A'&&a[i]<='Z')
            b++;   
        else if (a[i]>='a'&&a[i]<='z')  
            c++;
        else if (a[i]>='0'&&a[i]<='9')
            d++;
        else if (a[i]=' ')
            f++;
        else
            e++;
    }
    printf("大写字母、小写字母、数字字符、空格符以及其他字符的个数分别是：%d %d %d %d %d",b,c,d,e,f);
    return 0;
}