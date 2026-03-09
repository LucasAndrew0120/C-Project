#include<stdio.h>
int main()
{
    double v1,v2;
    printf("请输入你的车速和车道限速：");
    scanf("%lf %lf",&v1,&v2);
    if (v1<=v2)
        printf("你没有超速");
    else if ((v1>v2)&&(v1<=v2*1.1))
        printf("你超速了");
    else if ((v1>v2*1.1)&&(v1<v2*1.3))
        printf("你超出车道限速的10%%，处200元罚款");
    else if ((v1>v2*1.3)&&(v1<v2*1.5))
        printf("你超出车道限速的30%%，处400元罚款");
    else if (v1>v2*1.5)
        printf("你超出车道限速的50%%，处吊销驾驶证");
    getchar();
    return 0;
}