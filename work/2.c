#include<stdio.h>
int main()
{
    int n,i;
    printf("请输入序号以查询水果单价:\n");
    printf("[1] apple [2] pear [3] orange [4] grape [0] exit:\n");
    
    for (i=0;i<5;i++)
    {
        scanf("%d",&n);
        switch (n)
        {
        case 1:
            printf("3.00元/公斤\n");
            break;
        case 2:
            printf("2.50元/公斤\n");
            break;
        case 3:
            printf("4.10元/公斤\n");
            break;
        case 4:
            printf("10.20元/公斤\n");
            break;
        default:
            printf("0");
            break;
        }
        if (n==0&&i<5)
            break;
    }
}