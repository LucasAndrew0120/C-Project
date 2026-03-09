#include<stdio.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>

int generateRandomNumber(int a)
{
    a = rand() % 99 + 1;
    return a;
}

int getUserGuess(int b)
{
    scanf("%d", &b);
    return b;
}

int checkGuess(int a, int c) 
{
    int b;
    int n = 0; // 用于记录当前的猜测次数
    int i;
    
    for (i = 0; i < c; i++) // 循环c次
    {
        printf("请输入你要猜的数： \n");
        b = getUserGuess(b);
        n++; // 只要输入了，次数就加1

        // 1. 先判断是否输入负数
        if (b < 0) 
        {
            n = -1; 
            break;
        } 
        
        // 2. 判断是否猜中
        if (a == b) 
        {
            if (n == 1) n = 0;       // 1次猜中，对应Bingo!
            else if (n <= 3) n = -3; // 3次以内，对应Lucky You!
            else n = -2;             // N次以内，对应Good Guess!
            break;
        } 
        // 3. 没猜中，提示大小
        else if (a > b) 
        {
            printf("Too small\n");
        } 
        else if (a < b) 
        {
            printf("Too big\n");
        }

        // 4. 如果到了最后一次还没猜中
        if (i == c - 1) 
        {
            n = -1;
        }
    }
    return n;  
}

void printResult(int n, int c)
{
    switch (n)
    {
    case 0:
        printf("Bingo!");
        break;
    case -3:
        printf("Lucky You!");
        break;
    case -2:
        printf("Good Guess!");
        break;
    case -1:
        printf("Game Over");
        break;
    }
}

int main()
{
    int a, n, i, c;
    srand((unsigned int)time(NULL));
    a = generateRandomNumber(0); // 传入一个初始值即可
    printf("这是一个猜数游戏,范围是小于100的正整数,请你自定义你的猜测次数：\n");
    scanf("%d", &c);
    n = checkGuess(a, c);
    printResult(n, c);
    return 0;
}