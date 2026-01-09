#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 中英文姓名库
const char *chinese_names[] = {
    // 男性中文名
    "张伟", "王伟", "李伟", "刘伟", "陈伟", "杨伟", "赵伟", "黄伟", "周杰",
    "吴刚", "胡强", "林涛", "徐明", "孙军", "马超", "朱勇", "何亮", "高飞",
    "郭强", "罗刚", "郑阳", "谢军", "韩磊", "唐勇", "冯超", "董健", "萧峰",
    "程龙", "曹勇", "袁弘",

    // 女性中文名
    "李娜", "王芳", "张敏", "刘静", "陈丽", "杨艳", "赵霞", "黄娟", "周婷",
    "吴倩", "胡洁", "林雪", "徐琳", "孙悦", "马玲", "朱梅", "何婷", "高莹",
    "郭蕾", "罗薇", "郑娜", "谢芳", "韩梅", "唐琳", "冯洁", "董婷", "萧雨",
    "程芳", "曹颖", "袁媛"};

const char *english_names[] = {
    // 男性英文名
    "John", "David", "Michael", "Robert", "William", "James", "Charles",
    "Thomas", "Daniel", "Matthew", "Anthony", "Mark", "Paul", "Steven",
    "Andrew", "Kenneth", "George", "Joshua", "Kevin", "Brian", "Edward",
    "Ronald", "Timothy", "Jason",

    // 女性英文名
    "Mary", "Lisa", "Sarah", "Jennifer", "Emily", "Jessica", "Amanda",
    "Michelle", "Ashley", "Melissa", "Stephanie", "Laura", "Rebecca", "Rachel",
    "Kimberly", "Nicole", "Christine", "Katherine", "Samantha", "Elizabeth",
    "Heather", "Tiffany", "Amy", "Angela"};

// 时间段（6个时段，08:00-20:00）
const char *time_slots[] = {"08:00", "10:00", "12:00", "14:00", "16:00", "18:00"};
const int num_time_slots = 6;  // 修改为6个时段
#define TOTAL_SEATS 50  // 50个机位

// 从时间段字符串提取小时（如"08:00" -> 8）
int extract_hour_from_time(const char* time_str) {
    int hour;
    if (sscanf(time_str, "%d:", &hour) == 1) {
        return hour;
    }
    return -1;
}

// 获取时间段索引 (08:00=0, 10:00=1, 12:00=2, 14:00=3, 16:00=4, 18:00=5)
int get_time_slot_index(int hour) { 
    return (hour - 8) / 2; 
}

// 生成随机姓名（考虑性别）
void generate_random_name(char *name, int gender) {
    if (rand() % 2 == 0) {  // 50%中文名
        if (gender == 1) {  // 男性
            int index = 0 + rand() % 30;
            strcpy(name, chinese_names[index]);
        } else {  // 女性
            int index = 30 + rand() % 30;
            strcpy(name, chinese_names[index]);
        }
    } else {  // 50%英文名
        if (gender == 1) {  // 男性
            int index = 0 + rand() % 24;
            strcpy(name, english_names[index]);
        } else {  // 女性
            int index = 24 + rand() % 24;
            strcpy(name, english_names[index]);
        }
    }
}

// 生成随机电话号码
void generate_random_phone(char *phone) {
    phone[0] = '1';
    const char second_digits[] = "3456789";
    phone[1] = second_digits[rand() % 7];
    for (int i = 2; i < 11; i++) {
        phone[i] = '0' + rand() % 10;
    }
    phone[11] = '\0';
}

// 生成一天的数据（按照预约系统的格式）
int generate_daily_data(FILE *file, int year, int month, int day) {
    // 初始化一天的记录 - 修复：使用显式循环初始化
    int daily_occupancy[TOTAL_SEATS][num_time_slots];
    char daily_names[TOTAL_SEATS][num_time_slots][20];
    int daily_genders[TOTAL_SEATS][num_time_slots];
    char daily_phones[TOTAL_SEATS][num_time_slots][12];
    
    // 使用循环初始化数组
    for (int seat = 0; seat < TOTAL_SEATS; seat++) {
        for (int time_idx = 0; time_idx < num_time_slots; time_idx++) {
            daily_occupancy[seat][time_idx] = 0;
            daily_genders[seat][time_idx] = 0;
            strcpy(daily_names[seat][time_idx], "");
            strcpy(daily_phones[seat][time_idx], "");
        }
    }
    
    int total_records_today = 0;

    // 为每个时段生成随机数量的记录
    for (int time_idx = 0; time_idx < num_time_slots; time_idx++) {
        // 每个时段随机生成10-30条记录
        int records_this_slot = 10 + rand() % 21;
        
        for (int i = 0; i < records_this_slot && i < TOTAL_SEATS; i++) {
            // 随机选择一个机位（1-50）
            int seat = rand() % TOTAL_SEATS;  // 0-49
            
            // 检查该机位在该时段是否已被使用
            if (daily_occupancy[seat][time_idx] == 1) {
                // 如果已被使用，找下一个空闲机位
                for (int s = 0; s < TOTAL_SEATS; s++) {
                    if (daily_occupancy[s][time_idx] == 0) {
                        seat = s;
                        break;
                    }
                }
                if (daily_occupancy[seat][time_idx] == 1) continue; // 没有空闲机位
            }
            
            // 标记为已使用
            daily_occupancy[seat][time_idx] = 1;
            
            // 生成人员信息
            int gender = rand() % 2;
            generate_random_name(daily_names[seat][time_idx], gender);
            generate_random_phone(daily_phones[seat][time_idx]);
            daily_genders[seat][time_idx] = gender;
            
            total_records_today++;
        }
    }
    
    // 写入这一天数据（按照预约系统的格式）
    // 先写入年月日
    fprintf(file, "%d %d %d\n", year, month, day);
    
    // 写入每个机位每个时段的数据
    for (int seat = 0; seat < TOTAL_SEATS; seat++) {
        for (int time_idx = 0; time_idx < num_time_slots; time_idx++) {
            fprintf(file, "%d", daily_occupancy[seat][time_idx]);
            
            if (daily_occupancy[seat][time_idx] == 1) {
                fprintf(file, " %s %d %s", 
                        daily_names[seat][time_idx],
                        daily_genders[seat][time_idx],
                        daily_phones[seat][time_idx]);
            } else {
                fprintf(file, " None 0 None");
            }
            
            if (time_idx < num_time_slots - 1) {
                fprintf(file, " ");
            }
        }
        fprintf(file, "\n");
    }
    
    return total_records_today;
}

int main() {
    srand(time(NULL));
    
    // 修改文件名
    FILE *file = fopen("computer_room_data.txt", "w");
    if (file == NULL) {
        printf("无法创建文件！\n");
        return 1;
    }
    
    // 生成多天数据
    int start_year = 2026;
    int start_month = 1;
    int start_day = 1;
    int num_days = 30;  // 生成30天数据
    
    // 先写入天数
    fprintf(file, "%d\n", num_days);
    
    int total_records = 0;
    
    printf("正在生成机房监控数据...\n");
    printf("机房配置：固定50个机位\n");
    printf("监控时段：08:00-20:00，每2小时一次\n");
    printf("输出格式：TXT文件（兼容预约系统格式）\n\n");
    
    for (int day = start_day; day < start_day + num_days; day++) {
        int daily_records = generate_daily_data(file, start_year, start_month, day);
        total_records += daily_records;
        
        printf("已生成: %04d年%02d月%02d日 - %d条记录\n", 
               start_year, start_month, day, daily_records);
    }
    
    fclose(file);
    
    printf("\n=============================================\n");
    printf("数据生成完成！\n");
    printf("总天数: %d天\n", num_days);
    printf("总占用记录数: %d条\n", total_records);
    printf("保存到: computer_room_data.txt\n");
    printf("=============================================\n");
    
    return 0;
}