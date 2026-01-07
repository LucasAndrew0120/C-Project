#include <stdio.h>
#include <math.h>

#define EPSILON 1e-6
#define MAX_ITER 1000
#define MAX_ROOTS 10

// 函数定义：f(x) = x^4 - 2x^2 + x
double f(double x) {
    return pow(x, 4) - 2 * pow(x, 2) + x;
}

// 导函数定义：f'(x) = 4x^3 - 4x + 1
double df(double x) {
    return 4 * pow(x, 3) - 4 * x + 1;
}

// 牛顿迭代法
double newton_method(double x0) {
    double x = x0;
    int iter = 0;
    
    while (iter < MAX_ITER) {
        double fx = f(x);
        double dfx = df(x);
        
        if (fabs(dfx) < EPSILON) {
            printf("警告：在 x = %f 处导数为零，无法继续迭代\n", x);
            return NAN;
        }
        
        double x_new = x - fx / dfx;
        
        if (fabs(x_new - x) < EPSILON) {
            return x_new;
        }
        
        x = x_new;
        iter++;
    }
    
    printf("警告：在 x0 = %f 处达到最大迭代次数，可能未收敛\n", x0);
    return NAN;
}

// 检查根是否已存在
int is_root_exists(double roots[], int count, double root) {
    for (int i = 0; i < count; i++) {
        if (fabs(roots[i] - root) < EPSILON) {
            return 1;
        }
    }
    return 0;
}

int main() {
    double roots[MAX_ROOTS];
    int root_count = 0;
    
    printf("使用牛顿迭代法求解方程: f(x) = x^4 - 2x^2 + x = 0\n");
    printf("在区间 [-2, 2] 内搜索根...\n\n");
    
    // 在区间 [-2, 2] 内以不同初始值搜索根
    for (double x0 = -2.0; x0 <= 2.0; x0 += 0.2) {
        double root = newton_method(x0);
        
        if (!isnan(root) && !is_root_exists(roots, root_count, root)) {
            roots[root_count++] = root;
            printf("找到根: x = %f, f(x) = %e\n", root, f(root));
            
            if (root_count >= MAX_ROOTS) {
                break;
            }
        }
    }
    
    printf("\n共找到 %d 个根:\n", root_count);
    for (int i = 0; i < root_count; i++) {
        printf("根 %d: x = %f\n", i + 1, roots[i]);
    }
    
    return 0;
}