#include<stdio.h>
#include<string.h>

int main()
{
    char a[100] = {0};
    int i, n, isPalindrome = 1;
    
    printf("请输入正整数，不超过100位：");
    scanf("%s", a);
    
    n = strlen(a);  // 使用strlen获取字符串长度
    
    for (i = 0; i < n / 2; i++)
    {
        if (a[i] != a[n - 1 - i])
        {
            isPalindrome = 0;
            break;
        }
    }
    
    if (isPalindrome)
    {
        printf("这个数是回文数\n");
    }
    else
    {
        printf("这个数不是回文数\n");
    }
    
    return 0;
}