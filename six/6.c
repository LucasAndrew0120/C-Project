/*
#include<stdio.h>
#include<string.h>
void Ave_Sum(float array[][4], int n, int *ave, int *sum)
{
    int i,j;
    float array2[3][4];
    printf("一个有几个同学呢?");
    scanf("%d",&n);
    for (i=0;i<n;i++)
    {
        printf("请输入第%d个同学的四科成绩",i+1);
        for (j=0;j<4;j++)
        {
            scanf("%f",&array[i][j]);
        }
    }
    memccpy(array2,array,sizeof(array));
    for ( i = 0; i < 4; i++)
    {
        ave=(int)array[j][i];
        for ( j = 0; j < n; j++)
        {
            *sum=(float)*sum+array[j][i];
        }
        *ave=(float)*sum/3;
    }
    for (i=0;i<n;i++)
    {
        j=0;
        sum=(int)array2[i][j];
        for(j=1;j<4;j++)
        {
            *sum=*sum+array2[i][j];
        } 
    }
    printf("四科平均成绩分别为：");
    for (i=0;i<4;i++)
    {
        printf("%f",*ave);
        ave++;
    }
    printf("三位学生的总成绩分别为：");
    for (i=0;i<n;i++)
    {
        printf("%f",*sum);
        sum++;
    }
}
*/
#include <stdio.h>
#include <string.h>

// 按照题目原型编写
void Ave_Sum(float array[][4], int n, int *ave, int *sum)
{
    int i, j;
    float col_sum; // 用于辅助计算每科总分
    float row_sum; // 用于辅助计算每个学生总分

    // 1. 输入数据 (保留你的逻辑)
    for (i = 0; i < n; i++)
    {
        printf("请输入第 %d 个同学的 4 科成绩：", i + 1);
        for (j = 0; j < 4; j++)
        {
            scanf("%f", &array[i][j]);
        }
    }

    // 2. 计算每一科的平均成绩 (纵向遍历：固定列，走行)
    for (i = 0; i < 4; i++)
    {
        col_sum = 0;
        for (j = 0; j < n; j++)
        {
            col_sum += array[j][i];
        }
        *(ave + i) = (int)(col_sum / n); // 计算平均分并存入 ave 指针指向的位置
    }

    // 3. 计算每个学生的总成绩 (横向遍历：固定行，走列)
    for (i = 0; i < n; i++)
    {
        row_sum = 0;
        for (j = 0; j < 4; j++)
        {
            row_sum += array[i][j];
        }
        *(sum + i) = (int)row_sum; // 计算总分并存入 sum 指针指向的位置
    }

    // 4. 打印结果
    printf("\n4 科平均成绩分别为：");
    for (i = 0; i < 4; i++)
    {
        printf("%d ", *(ave + i));
    }

    printf("\n%d 位学生的总成绩分别为：", n);
    for (i = 0; i < n; i++)
    {
        printf("%d ", *(sum + i));
    }
    printf("\n");
}

int main()
{
    float a[3][4];
    int ave_res[4]; // 存放 4 科平均分
    int sum_res[3]; // 存放 3 个学生总分
    int n = 3;

    // 调用函数
    Ave_Sum(a, n, ave_res, sum_res);

    return 0;
}