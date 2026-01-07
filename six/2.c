#include<stdio.h>
#include<string.h>
int word(char a[100])  //自定义函数
{
    int i,temp=1; //temp起始值为一，确保单词比空格多一个
    int len=strlen(a);
    for (i=0;i<len;i++)
    {
        if (a[i]==' ')
            temp++;
    }
    return temp;
}
int main()
{
    int num=0;
    char b[100];
    printf("请输入一句英文句子：");
    gets(b);
    num=word(b);
    printf("句子里一共有%d个单词",num);
    return 0;
}
