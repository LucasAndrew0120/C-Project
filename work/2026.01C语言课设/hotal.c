#include <stdio.h>
#include <string.h>
#include <windows.h>

typedef struct cusinfo
{
    char name[20];
    int sex;
    char tel[12];
} cinfo;

typedef struct mechine
{
    int state[6];
    cinfo waitlist[6];
    int year;
    int month;
    int day;
} device;

device info[100];

// 1 & 4 功能合并：查询机位
void search(device info[])
{
    int i, year, month, day, found = 0;
    printf("请输入查询日期 (格式: year/month/day): ");
    scanf("%d/%d/%d", &year, &month, &day);
    for (i = 0; i < 100; i++)
    {
        if (year == info[i].year && month == info[i].month &&
            day == info[i].day)
        {
            found = 1;
            for (int j = 0; j < 6; j++)
            {
                printf("[%02d:00-%02d:00] ", 2 * j + 8, 2 * j + 10);
                if (info[i].state[j] == 0)
                    printf("状态: 空闲\n");
                else
                    printf("状态: 已预约 | 顾客: %s | 性别: %d | 电话: %s\n",
                           info[i].waitlist[j].name, info[i].waitlist[j].sex,
                           info[i].waitlist[j].tel);
            }
            break;
        }
    }
    if (!found)
        printf("未找到该日期的记录。\n");
}

// 机位预订
void buy(device info[])
{
    int t1, t2;
    printf("请输入想要的时间段 (格式: 08:00-10:00): ");
    scanf("%d:00-%d:00", &t1, &t2);

    int time_slot = (t1 - 8) / 2;

    // 在所有日期中查找该时间段空闲的
    printf("以下日期在 %02d:00-%02d:00 时段有空位：\n", t1, t2);
    int available_dates[100];
    int count = 0;

    for (int i = 0; i < 100; i++)
    {
        if (info[i].year != 0 && info[i].state[time_slot] == 0)
        {
            available_dates[count++] = i;
            printf("%d. %d/%d/%d\n", count, info[i].year, info[i].month,
                   info[i].day);
        }
    }

    if (count == 0)
    {
        printf("该时间段在所有日期都已被占用。\n");
        // 可以查找其他时间段
        return;
    }

    // 让用户选择日期
    printf("请选择日期编号（1-%d）: ", count);
    int choice;
    scanf("%d", &choice);

    if (choice >= 1 && choice <= count)
    {
        int idx = available_dates[choice - 1];

        printf("请输入个人信息[姓名 性别(男1女0) 电话]: ");
        scanf("%s %d %s", info[idx].waitlist[time_slot].name,
              &info[idx].waitlist[time_slot].sex,
              info[idx].waitlist[time_slot].tel);
        info[idx].state[time_slot] = 1;
        printf("预约成功！\n");
    }
}

// 取消预订
void exit_buy(device info[])
{
    int year, month, day;
    char name[20];
    printf("请输入原预订日期 (year/month/day) 和姓名: ");
    scanf("%d/%d/%d %s", &year, &month, &day, name);
    for (int i = 0; i < 100; i++)
    {
        if (year == info[i].year && month == info[i].month &&
            day == info[i].day)
        {
            for (int j = 0; j < 6; j++)
            {
                if (info[i].state[j] == 1 &&
                    strcmp(name, info[i].waitlist[j].name) == 0)
                {
                    info[i].state[j] = 0;
                    strcpy(info[i].waitlist[j].name, "None");
                    printf("取消成功！\n");
                    return;
                }
            }
        }
    }
    printf("未找到匹配的预约信息。\n");
}

void read_data(device info[])
{
    FILE *fp = fopen("data.txt", "r");
    if (!fp)
        return;
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            fscanf(fp, "%d %d %d %d %s %d %s", &info[i].year, &info[i].month,
                   &info[i].day, &info[i].state[j], info[i].waitlist[j].name,
                   &info[i].waitlist[j].sex, info[i].waitlist[j].tel);
            if (strcmp(info[i].waitlist[j].name, "None") == 0)
                strcpy(info[i].waitlist[j].name, "");
        }
    }
    fclose(fp);
}

void save_data(device info[])
{
    FILE *fp = fopen("data.txt", "w");
    if (!fp) //空文件指针，直接返回
        return;
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            char temp_name[20], temp_tel[12];
            strcpy(temp_name, strlen(info[i].waitlist[j].name) > 0
                                  ? info[i].waitlist[j].name
                                  : "None");
            strcpy(temp_tel, strlen(info[i].waitlist[j].tel) > 0
                                 ? info[i].waitlist[j].tel
                                 : "None");
            fprintf(fp, "%d %d %d %d %s %d %s\n", info[i].year, info[i].month,
                    info[i].day, info[i].state[j], temp_name,
                    info[i].waitlist[j].sex, temp_tel);
        }
    }
    fclose(fp);
}

int main()
{
    SetConsoleOutputCP(65001);
    int n = 0;
    read_data(info);
    while (n != 4)
    {
        printf("\n--- 机房预约系统 ---\n1.查询 | 2.预订 | 3.取消 | "
               "4.保存并退出\n请选择: ");
        scanf("%d", &n);
        switch (n)
        {
        case 1:
            search(info);
            break;
        case 2:
            buy(info);
            break;
        case 3:
            exit_buy(info);
            break;
        case 4:
            save_data(info);
            break;
        }
    }
    return 0;
}