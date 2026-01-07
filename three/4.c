#include <stdio.h>
#include <math.h>

int main() {
    double a, b, c;
    double delta, x1, x2, realPart, imagPart;
    
    printf("请输入一元二次方程的系数(a, b, c): ");
    scanf("%lf %lf %lf", &a, &b, &c);
    
    if(a == 0) {
        // 不是一元二次方程
        if(b == 0) {
            if(c == 0) {
                printf("方程为0=0，有无穷多解\n");
            } else {
                printf("方程为%.2f=0，无解\n", c);
            }
        } else {
            x1 = -c / b;
            printf("这是一元一次方程，根为: x = %.2f\n", x1);
        }
    } else {
        // 是一元二次方程
        delta = b * b - 4 * a * c;
        
        if(delta > 0) {
            // 两个不等实根
            x1 = (-b + sqrt(delta)) / (2 * a);
            x2 = (-b - sqrt(delta)) / (2 * a);
            printf("方程有两个不等实根:\n");
            printf("x1 = %.2f\n", x1);
            printf("x2 = %.2f\n", x2);
        } else if(delta == 0) {
            // 两个相等实根
            x1 = -b / (2 * a);
            printf("方程有两个相等实根:\n");
            printf("x1 = x2 = %.2f\n", x1);
        } else {
            // 两个共轭复根
            realPart = -b / (2 * a);
            imagPart = sqrt(-delta) / (2 * a);
            printf("方程有两个共轭复根:\n");
            printf("x1 = %.2f + %.2fi\n", realPart, imagPart);
            printf("x2 = %.2f - %.2fi\n", realPart, imagPart);
        }
    }
    
    return 0;
}