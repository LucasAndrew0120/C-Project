#include<stdio.h>
#include<string.h>

typedef struct cusinfo {
    char name[20];
    int sex;
    char tel[12];
} cinfo;

typedef struct mechine {
    int state[6];
    cinfo waitlist[6];
    int year;
    int month;
    int day;
} device;

device info[100];

// 1 & 4 功能合并：查询机位
void search(device info[]) {
    int i, year, month, day, found = 0;
    printf("请输入查询日期 (格式: year/month/day): ");
    scanf("%d/%d/%d", &year, &month, &day);
    for (i = 0; i < 100; i++) {
        if (year == info[i].year && month == info[i].month && day == info[i].day) {
            found = 1;
            for (int j = 0; j < 6; j++) {
                printf("[%02d:00-%02d:00] ", 2 * j + 8, 2 * j + 10);
                if (info[i].state[j] == 0)
                    printf("状态: 空闲\n");
                else
                    printf("状态: 已预约 | 顾客: %s | 性别: %d | 电话: %s\n",
                           info[i].waitlist[j].name, info[i].waitlist[j].sex, info[i].waitlist[j].tel);
            }
            break;
        }
    }
    if (!found) printf("未找到该日期的记录。\n");
}

// 2. 机位预订
void buy(device info[]) {
    int i, j, year, month, day, t1, t2, found = 0;
    printf("请输入预订日期和时段 (格式: year/month/day/08:00-10:00): ");
    if (scanf("%d/%d/%d/%d:00-%d:00", &year, &month, &day, &t1, &t2) != 5) return;

    j = (t1 - 8) / 2;
    if (j < 0 || j > 5) { printf("时间段无效。\n"); return; }

    for (i = 0; i < 100; i++) {
        if (year == info[i].year && month == info[i].month && day == info[i].day) {
            found = 1;
            if (info[i].state[j] == 0) { // 时段空闲直接预约
                printf("请输入个人信息 (姓名 性别[1男0女] 电话): ");
                scanf("%s %d %s", info[i].waitlist[j].name, &info[i].waitlist[j].sex, info[i].waitlist[j].tel);
                info[i].state[j] = 1;
                printf("预约成功！\n");
            } else { // 已被占用，寻找最近空闲
                printf("该时段已被占用。正在尝试寻找其他空闲时段...\n");
                int alt_j = -1;
                for(int k=0; k<6; k++) if(info[i].state[k] == 0) { alt_j = k; break; }
                
                if (alt_j != -1) {
                    printf("找到当天 %02d:00-%02d:00 有空位，是否预约？(1.是 0.否): ", 2*alt_j+8, 2*alt_j+10);
                    int choice; scanf("%d", &choice);
                    if(choice == 1) {
                        scanf("%s %d %s", info[i].waitlist[alt_j].name, &info[i].waitlist[alt_j].sex, info[i].waitlist[alt_j].tel);
                        info[i].state[alt_j] = 1;
                        printf("预约成功！\n");
                    }
                } else {
                    printf("当天已满，请通过查询功能寻找其他日期的空位。\n");
                }
            }
            break;
        }
    }
    if (!found) printf("日期未初始化。\n");
}

// 3. 退出预订
void exit_buy(device info[]) {
    int year, month, day;
    char name[20];
    printf("请输入原预订日期 (year/month/day) 和姓名: ");
    scanf("%d/%d/%d %s", &year, &month, &day, name);
    for (int i = 0; i < 100; i++) {
        if (year == info[i].year && month == info[i].month && day == info[i].day) {
            for (int j = 0; j < 6; j++) {
                if (info[i].state[j] == 1 && strcmp(name, info[i].waitlist[j].name) == 0) {
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

void read_data(device info[]) {
    FILE *fp = fopen("data.txt", "r");
    if (!fp) return;
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 6; j++) {
            fscanf(fp, "%d %d %d %d %s %d %s", &info[i].year, &info[i].month, &info[i].day, 
                   &info[i].state[j], info[i].waitlist[j].name, &info[i].waitlist[j].sex, info[i].waitlist[j].tel);
            if (strcmp(info[i].waitlist[j].name, "None") == 0) strcpy(info[i].waitlist[j].name, "");
        }
    }
    fclose(fp);
}

void save_data(device info[]) {
    FILE *fp = fopen("data.txt", "w");
    if (!fp) return;
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 6; j++) {
            char temp_name[20], temp_tel[12];
            strcpy(temp_name, strlen(info[i].waitlist[j].name) > 0 ? info[i].waitlist[j].name : "None");
            strcpy(temp_tel, strlen(info[i].waitlist[j].tel) > 0 ? info[i].waitlist[j].tel : "None");
            fprintf(fp, "%d %d %d %d %s %d %s\n", info[i].year, info[i].month, info[i].day, 
                    info[i].state[j], temp_name, info[i].waitlist[j].sex, temp_tel);
        }
    }
    fclose(fp);
}

int main() {
    int n = 0;
    read_data(info);
    while (n != 4) {
        printf("\n--- 机房预约系统 ---\n1.查询 | 2.预订 | 3.取消 | 4.保存并退出\n请选择: ");
        scanf("%d", &n);
        switch (n) {
            case 1: search(info); break;
            case 2: buy(info); break;
            case 3: exit_buy(info); break;
            case 4: save_data(info); break;
        }
    }
    return 0;
}