#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct 
{
    int num;
    char name[20];
    int math;
    int c;
    float ave,total;
} stu;
int complete(const void *a,const void *b)
{
    stu *s1=(stu *)a;
    stu *s2=(stu *)b;
    return s2->total-s1->total;
}
int list(int n,stu class[])
{
   int i; 
   printf("请输入学生人数：");
   scanf("%d",&n);
   for (i=0;i<n;i++)
   {
        printf("请输入第 %d 个人的学号,姓名,数学成绩,C语言成绩: ", i + 1);
        // 使用 class[i].成员名 来定位
        scanf("%d %s %d %d", &class[i].num, class[i].name, &class[i].math, &class[i].c);
        class[i].ave=(class[i].math+class[i].c)/2.0;
        class[i].total=class[i].math+class[i].c;
   }
   return n;
}
int main()
{
    int n,i;
    stu class[100];
    FILE *fp; // 定义文件指针
    n=list(n,class);
    qsort(class,n,sizeof(stu),complete);
    for (i=0;i<n;i++)
    {
        printf("|学号|姓名|数学成绩|C语言成绩|平均分|总分|\n");
        printf("|%d|%s|%d|%d|%.2f|%.2f|\n",class[i].num,class[i].name,class[i].math,class[i].c,class[i].ave,class[i].total);
    }
    fp = fopen("result.txt", "w"); // 以写入模式打开文件
    if (fp == NULL) {
        printf("文件打开失败！\n");
        return 1;
    }
    fprintf(fp, "|学号|姓名|数学成绩|C语言成绩|平均分|总分|\n"); // 写入表头
    for (i = 0; i < n; i++)
    {
        // 将 printf 改为 fprintf，并指定文件指针 fp
        fprintf(fp, "|%d|%s|%d|%d|%.2f|%.2f|\n", 
                class[i].num, class[i].name, class[i].math, class[i].c, class[i].ave, class[i].total);
    }   
    fclose(fp); // 必须关闭文件
    printf("\n信息已成功存入 result.txt 文件中。\n");

    return 0;
}