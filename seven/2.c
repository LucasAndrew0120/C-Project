#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int mystrcpy( char *str1,char *str2,char one[100],char two[100])
{
    int i;
    int len1=strlen(one);
    int len2=strlen(two);
    str1=&one[0];
    str2=&two[0];
    for (i=0;i<len1;i++)
    {
        if (one[i]>'0'&&one[i]<'9')
        {
            *str2=one[i];
            str2++;
        }
    }
    *str2='\0';
    return 0;
}
int main()
{
    char *str1;
    char *str2;
    char one[100];
    char two[100];
    printf("请输入一段带有数字的字符串,程序会自动找出并输出");
    gets(one);
    mystrcpy(str1,str2,one,two);
    printf("%s",&two);
    return 0;
}
