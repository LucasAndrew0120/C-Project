#include<stdio.h>
#include<string.h>

void num(char x[100])
{
    int i, j, len;
    len = strlen(x);
    char result[200];
    int k = 0;
    
    for (i = 0; i < len; i++)
    {
        if (x[i] >= '0' && x[i] <= '9')
        {
            result[k++] = '#';
            result[k++] = x[i];
        }
        else
        {
            result[k++] = x[i];
        }
    }
    result[k] = '\0';
    printf("%s", result);
}

int main()
{
    char a[100];
    printf("请输入你的字符，小于十个:\n");
    fgets(a, sizeof(a), stdin);
    num(a);
    return 0;
}