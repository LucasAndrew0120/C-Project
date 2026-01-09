#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define MAX_DAYS 100   // 最大存储天数
#define Time 6   // 6个时段：08:00-20:00，每2小时
#define States 50 // 50个机位
// 客户信息结构体
typedef struct cusinfo
{
    char name[20];
    int sex;      // 0:女, 1:男
    char tel[12]; // 11位电话号码
} cinfo;
// 机位信息结构体（按日期组织）
typedef struct mechine
{
    int year;
    int month;
    int day;
    // 50个机位，每个机位6个时段的状态和预约信息
    int state[States][Time];      // 状态：0空闲，1占用
    cinfo waitlist[States][Time]; // 预约信息
} device;
device info[MAX_DAYS]; // 存储多天的数据
int day_count = 0;     // 实际存储的天数
// 获取时间段索引 (08:00=0, 10:00=1, 12:00=2, 14:00=3, 16:00=4, 18:00=5)
int get_time_slot_index(int hour) { return (hour - 8) / 2; }
// 获取时间段字符串
char *get_time_slot_str(int slot)
{
    static char time_str[20];
    int start_hour = 8 + slot * 2;
    sprintf(time_str, "%02d:00-%02d:00", start_hour, start_hour + 2);
    return time_str;
}
// 验证日期是否有效（月份1-12，日期1-30）
int validate_date(int year, int month, int day) {
    // 检查月份
    if (month < 1 || month > 12) {
        printf("月份无效！请输入1-12之间的数字。\n");
        return 0;
    }
    // 检查日期
    if (day < 1 || day > 30) {
        printf("日期无效！请输入1-30之间的数字。\n");
        return 0;
    }
    // 检查年份（可选，可以根据需要设置范围）
    if (year < 2000 || year > 2100) {
        printf("年份无效！请输入2000-2100之间的数字。\n");
        return 0;
    }
    return 1; // 日期有效
}
// 查找日期索引，如果不存在则创建
int find_or_create_date(int year, int month, int day)
{
    // 首先验证日期
    if (!validate_date(year, month, day)) {
        printf("日期无效，无法创建新日期记录。\n");
        return -1;
    }
    for (int i = 0; i < day_count; i++)
    {
        if (info[i].year == year && info[i].month == month &&
            info[i].day == day)
        {
            return i;
        }
    }
    // 如果没找到，创建新的日期记录
    if (day_count < MAX_DAYS)
    {
        int idx         = day_count;
        info[idx].year  = year;
        info[idx].month = month;
        info[idx].day   = day;
        // 初始化所有机位状态为空闲
        for (int seat = 0; seat < States; seat++)
        {
            for (int slot = 0; slot < Time; slot++)
            {
                info[idx].state[seat][slot] = 0; // 空闲
                strcpy(info[idx].waitlist[seat][slot].name, "");
                strcpy(info[idx].waitlist[seat][slot].tel, "");
                info[idx].waitlist[seat][slot].sex = 0;
            }
        }
        day_count++;
        return idx;
    }
    return -1; // 达到最大天数限制
}
// 1. 查询功能
void search(device info[])
{
    int choice;
    printf("\n=== 查询功能 ===\n");
    printf("1. 按日期查询所有机位状态\n");
    printf("2. 按机位查询所有日期状态\n");
    printf("3. 按客户信息查询预约记录\n");
    printf("请选择查询方式: ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
    {
        // 按日期查询
        int year, month, day;
        int valid_date = 0;
        // 循环直到输入有效日期
        while (!valid_date) {
            printf("请输入查询日期 (格式: year/month/day): ");
            scanf("%d/%d/%d", &year, &month, &day);
            if (validate_date(year, month, day)) {
                valid_date = 1;
            } else {
                printf("请重新输入日期。\n");
            }
        }
        int date_idx = -1;
        for (int i = 0; i < day_count; i++)
        {
            if (info[i].year == year && info[i].month == month &&
                info[i].day == day)
            {
                date_idx = i;
                break;
            }
        }
        if (date_idx == -1)
        {
            printf("该日期暂无数据。\n");
            return;
        }
        printf("\n日期: %d年%02d月%02d日\n", year, month, day);
        printf("机位状态总览:\n");
        printf("机位\\时段");
        for (int slot = 0; slot < Time; slot++)
        {
            printf("\t%s", get_time_slot_str(slot));
        }
        printf("\n");
        // 显示每个机位的状态
        for (int seat = 0; seat < States; seat++)
        {
            printf("机位%02d", seat + 1);
            for (int slot = 0; slot < Time; slot++)
            {
                printf("\t%s",
                       info[date_idx].state[seat][slot] ? "占用" : "空闲");
            }
            printf("\n");
        }
        // 显示详细预约信息
        printf("\n详细预约信息:\n");
        for (int seat = 0; seat < States; seat++)
        {
            for (int slot = 0; slot < Time; slot++)
            {
                if (info[date_idx].state[seat][slot] == 1)
                {
                    printf("机位%02d %s: 顾客: %s, 性别: %s, 电话: %s\n",
                           seat + 1, get_time_slot_str(slot),
                           info[date_idx].waitlist[seat][slot].name,
                           info[date_idx].waitlist[seat][slot].sex == 1 ? "男"
                                                                        : "女",
                           info[date_idx].waitlist[seat][slot].tel);
                }
            }
        }
        break;
    }
    case 2:
    {
        // 按机位查询
        int seat_num;
        printf("请输入要查询的机位号 (1-50): ");
        scanf("%d", &seat_num);
        if (seat_num < 1 || seat_num > States)
        {
            printf("机位号无效！\n");
            return;
        }
        int seat_idx = seat_num - 1;
        printf("\n机位 %d 的预约情况:\n", seat_num);
        int found = 0;
        for (int i = 0; i < day_count; i++)
        {
            for (int slot = 0; slot < Time; slot++)
            {
                if (info[i].state[seat_idx][slot] == 1)
                {
                    found = 1;
                    printf("日期: %d/%02d/%02d, 时间段: %s, 顾客: %s, 性别: "
                           "%s, 电话: %s\n",
                           info[i].year, info[i].month, info[i].day,
                           get_time_slot_str(slot),
                           info[i].waitlist[seat_idx][slot].name,
                           info[i].waitlist[seat_idx][slot].sex == 1 ? "男"
                                                                     : "女",
                           info[i].waitlist[seat_idx][slot].tel);
                }
            }
        }
        if (!found)
        {
            printf("该机位暂无预约记录。\n");
        }
        break;
    }
    case 3:
    {
        // 按客户信息查询
        char name[20];
        char tel[12];
        printf("请输入客户姓名: ");
        scanf("%s", name);
        printf("请输入客户电话: ");
        scanf("%s", tel);
        printf("\n%s (%s) 的预约记录:\n", name, tel);
        int found = 0;
        for (int i = 0; i < day_count; i++)
        {
            for (int seat = 0; seat < States; seat++)
            {
                for (int slot = 0; slot < Time; slot++)
                {
                    if (info[i].state[seat][slot] == 1 &&
                        strcmp(info[i].waitlist[seat][slot].name, name) == 0 &&
                        strcmp(info[i].waitlist[seat][slot].tel, tel) == 0)
                    {
                        found = 1;
                        printf("日期: %d/%02d/%02d, 机位: %02d, 时间段: %s\n",
                               info[i].year, info[i].month, info[i].day,
                               seat + 1, get_time_slot_str(slot));
                    }
                }
            }
        }
        if (!found)
        {
            printf("未找到该客户的预约记录。\n");
        }
        break;
    }
    default:
        printf("无效的选择！\n");
    }
}
// 2. 机位预订
void buy(device info[])
{
    int year, month, day, seat_num, start_hour;
    int valid_date = 0;
    printf("\n=== 机位预订 ===\n");
    // 循环直到输入有效日期
    while (!valid_date) {
        printf("请输入预订日期 (格式: year/month/day): ");
        scanf("%d/%d/%d", &year, &month, &day);
        if (validate_date(year, month, day)) {
            valid_date = 1;
        } else {
            printf("请重新输入日期。\n");
        }
    }
    printf("请输入机位号 (1-50): ");
    scanf("%d", &seat_num);
    if (seat_num < 1 || seat_num > States)
    {
        printf("机位号无效！\n");
        return;
    }
    printf("请选择时间段 (输入起始小时: 8,10,12,14,16,18): ");
    scanf("%d", &start_hour);
    if (start_hour < 8 || start_hour > 18 || (start_hour % 2 != 0))
    {
        printf("时间段无效！请选择8,10,12,14,16,18中的一个。\n");
        return;
    }
    int slot     = get_time_slot_index(start_hour);
    int seat_idx = seat_num - 1;
    // 查找或创建日期
    int date_idx = find_or_create_date(year, month, day);
    if (date_idx == -1)
    {
        printf("已达到最大存储天数限制！\n");
        return;
    }
    // 检查机位是否已被占用
    if (info[date_idx].state[seat_idx][slot] == 1)
    {
        printf("该机位在%s时段已被占用！\n", get_time_slot_str(slot));
        // 显示同时间段其他空闲机位
        printf("同时间段空闲机位: ");
        int found = 0;
        for (int s = 0; s < States; s++)
        {
            if (info[date_idx].state[s][slot] == 0)
            {
                printf("%d ", s + 1);
                found = 1;
            }
        }
        if (found)
            printf("\n");
        else
            printf("无\n");
        return;
    }
    // 获取客户信息
    printf("请输入客户信息:\n");
    printf("姓名: ");
    scanf("%s", info[date_idx].waitlist[seat_idx][slot].name);
    printf("性别 (0:女, 1:男): ");
    scanf("%d", &info[date_idx].waitlist[seat_idx][slot].sex);
    printf("电话 (11位): ");
    scanf("%s", info[date_idx].waitlist[seat_idx][slot].tel);
    // 更新状态
    info[date_idx].state[seat_idx][slot] = 1;
    printf("\n预订成功！\n");
    printf("预约信息: 日期 %d/%02d/%02d, 机位 %02d, 时间段 %s, 客户 %s\n", year,
           month, day, seat_num, get_time_slot_str(slot),
           info[date_idx].waitlist[seat_idx][slot].name);
}
// 3. 取消预订
void exit_buy(device info[])
{
    int year, month, day, seat_num, start_hour;
    char name[20], tel[12];
    int valid_date = 0;
    printf("\n=== 取消预订 ===\n");
    printf("请输入预订信息:\n");
    // 循环直到输入有效日期
    while (!valid_date) {
        printf("日期 (格式: year/month/day): ");
        scanf("%d/%d/%d", &year, &month, &day);
        if (validate_date(year, month, day)) {
            valid_date = 1;
        } else {
            printf("请重新输入日期。\n");
        }
    }
    printf("机位号 (1-50): ");
    scanf("%d", &seat_num);
    if (seat_num < 1 || seat_num > States)
    {
        printf("机位号无效！\n");
        return;
    }
    printf("时间段起始小时 (8,10,12,14,16,18): ");
    scanf("%d", &start_hour);
    printf("客户姓名: ");
    scanf("%s", name);
    printf("客户电话: ");
    scanf("%s", tel);
    int slot     = get_time_slot_index(start_hour);
    int seat_idx = seat_num - 1;
    // 查找日期
    int date_idx = -1;
    for (int i = 0; i < day_count; i++)
    {
        if (info[i].year == year && info[i].month == month &&
            info[i].day == day)
        {
            date_idx = i;
            break;
        }
    }
    if (date_idx == -1)
    {
        printf("未找到该日期的记录！\n");
        return;
    }
    // 验证预订信息
    if (info[date_idx].state[seat_idx][slot] == 1 &&
        strcmp(info[date_idx].waitlist[seat_idx][slot].name, name) == 0 &&
        strcmp(info[date_idx].waitlist[seat_idx][slot].tel, tel) == 0)
    {
        // 取消预订
        info[date_idx].state[seat_idx][slot] = 0;
        strcpy(info[date_idx].waitlist[seat_idx][slot].name, "");
        strcpy(info[date_idx].waitlist[seat_idx][slot].tel, "");
        info[date_idx].waitlist[seat_idx][slot].sex = 0;
        printf("取消预订成功！\n");
    }
    else
    {
        printf("未找到匹配的预订信息！请检查输入是否正确。\n");
    }
}
// 读取数据
void read_data(device info[])
{
    FILE *fp = fopen("computer_room_data.txt", "r");
    if (!fp)
    {
        printf("未找到数据文件，将创建新文件。\n");
        return;
    }
    // 读取天数
    fscanf(fp, "%d", &day_count);
    for (int i = 0; i < day_count && i < MAX_DAYS; i++)
    {
        fscanf(fp, "%d %d %d", &info[i].year, &info[i].month, &info[i].day);
        for (int seat = 0; seat < States; seat++)
        {
            for (int slot = 0; slot < Time; slot++)
            {
                fscanf(fp, "%d", &info[i].state[seat][slot]);
                if (info[i].state[seat][slot] == 1)
                {
                    fscanf(fp, " %s %d %s", info[i].waitlist[seat][slot].name,
                           &info[i].waitlist[seat][slot].sex,
                           info[i].waitlist[seat][slot].tel);
                }
                else
                {
                    // 跳过空信息
                    char dummy_name[20], dummy_tel[12];
                    int dummy_sex;
                    fscanf(fp, " %s %d %s", dummy_name, &dummy_sex, dummy_tel);
                    strcpy(info[i].waitlist[seat][slot].name, "");
                    strcpy(info[i].waitlist[seat][slot].tel, "");
                    info[i].waitlist[seat][slot].sex = 0;
                }
            }
        }
    }
    fclose(fp);
    printf("成功读取%d天的数据。\n", day_count);
}
// 保存数据
void save_data(device info[])
{
    FILE *fp = fopen("computer_room_data.txt", "w");
    if (!fp)
    {
        printf("无法创建数据文件！\n");
        return;
    }
    // 写入天数
    fprintf(fp, "%d\n", day_count);
    for (int i = 0; i < day_count; i++)
    {
        fprintf(fp, "%d %d %d\n", info[i].year, info[i].month, info[i].day);
        for (int seat = 0; seat < States; seat++)
        {
            for (int slot = 0; slot < Time; slot++)
            {
                fprintf(fp, "%d", info[i].state[seat][slot]);
                if (info[i].state[seat][slot] == 1)
                {
                    fprintf(fp, " %s %d %s", info[i].waitlist[seat][slot].name,
                            info[i].waitlist[seat][slot].sex,
                            info[i].waitlist[seat][slot].tel);
                }
                else
                {
                    fprintf(fp, " None 0 None");
                }
                if (slot < Time - 1)
                    fprintf(fp, " ");
            }
            fprintf(fp, "\n");
        }
    }
    fclose(fp);
    printf("数据已保存到 computer_room_data.txt，共%d天。\n", day_count);
}
int main()
{
    SetConsoleOutputCP(65001); // 支持中文输出
    // 初始化数组
    memset(info, 0, sizeof(info));
    // 读取已有数据
    read_data(info);
    int choice = 0;
    while (choice != 4)
    {
        printf("\n=== 机房机位预约系统 ===\n");
        printf("1. 查询机位状态\n");
        printf("2. 预订机位\n");
        printf("3. 取消预订\n");
        printf("4. 保存并退出\n");
        printf("请选择操作: ");
        scanf("%d", &choice);
        switch (choice)
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
            printf("感谢使用，再见！\n");
            break;
        default:
            printf("无效的选择，请重新输入！\n");
            break;
        }
    }
    return 0;
}