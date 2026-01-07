#include<stdio.h>
int main()
{
    double a[30]={0};
    double c=0.0;
    a[0]=2,a[1]=3;
    c=(double)a[0]/1+(double)a[1]/a[0];
    int i;
    for (i = 2; i<30; i++)
    {
        a[i]=a[i-1]+a[i-2];
        c+=(double)a[i]/a[i-1];
    }
    printf("%lf\n",c);
    return 0;
}
