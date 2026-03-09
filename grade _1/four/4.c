#include<stdio.h>
int main()
{
    char score[100]={0};
    int i,n;
    printf("请输入原始密码，不超过100字符：");
    scanf("%s",score);
    for (i = 0,n=0; score[i]!='\0'; i++)
    {
        n++;
    }
    printf("数组长度为：%d\n",n);
    for (i=0;i<n;i++)
    {
        if (score[i]>='A'&&score[i]<='V'||score[i]>='a'&&score[i]<='v')
            score[i]+=4;
        else if (score[i]>='W'&&score[i]<='Z'||score[i]>='w'&&score[i]<='z')
            score[i]-=22;
    }
    printf("密码为：%s",score);
    return 0;
}