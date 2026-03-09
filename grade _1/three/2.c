#include<stdio.h>
int main()
{
    char c;
    printf("please input a character:");
    c=getchar();
    if ((c>='A'&&c<='Z')||(c>='a'&&c<='z'))
        printf("键入的字符是字母");
    else if (c>='0'&&c<='9')
        printf("键入的字符是数字");
    else 
        printf("键入的字符是特殊字符");
    getchar();
    return 0;    
}