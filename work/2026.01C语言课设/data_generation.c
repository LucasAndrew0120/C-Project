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

// 时间段
const char *time_slots[] = {"08:00", "10:00", "12:00", "14:00",
                            "16:00", "18:00", "20:00"};
const int num_time_slots = 8;

// 生成随机姓名（考虑性别）
void generate_random_name(char *name, int gender)
{
    if (rand() % 2 == 0)
    { // 50%中文名
        if (gender == 1)
        {                                // 男性
            int index = 0 + rand() % 30; // 前30个是男性中文名
            strcpy(name, chinese_names[index]);
        }
        else
        {                                 // 女性
            int index = 30 + rand() % 30; // 后30个是女性中文名
            strcpy(name, chinese_names[index]);
        }
    }
    else
    { // 50%英文名
        if (gender == 1)
        {                                // 男性
            int index = 0 + rand() % 24; // 前24个是男性英文名
            strcpy(name, english_names[index]);
        }
        else
        {                                 // 女性
            int index = 24 + rand() % 24; // 后24个是女性英文名
            strcpy(name, english_names[index]);
        }
    }
}

// 生成随机电话号码
void generate_random_phone(char *phone)
{
    // 中国手机号格式：1[3-9]XXXXXXXXX
    phone[0] = '1';

    const char second_digits[] = "3456789";
    phone[1]                   = second_digits[rand() % 7];

    for (int i = 2; i < 11; i++)
    {
        phone[i] = '0' + rand() % 10;
    }
    phone[11] = '\0';
}

// 生成一天的数据
int generate_daily_data(FILE *file, int year, int month, int day)
{
    int total_records_today = 0;

    // 使用集合来跟踪已使用的机位，避免重复（在实际机房中，同一时间同一机位不能有多个记录）
    int used_seats[8][51] = {0}; // 8个时段 × 51个机位（1-50）

    // 为每个时段生成随机数量的记录（0-50条，但不超过可用机位数）
    for (int time_idx = 0; time_idx < num_time_slots; time_idx++)
    {
        // 每个时段随机生成5-35条记录（保证一定数据量，但不超过机位数）
        int records_this_slot = 5 + rand() % 31; // 5-35条

        // 记录生成的记录数，用于统计
        int actual_records = 0;

        for (int i = 0; i < records_this_slot; i++)
        {
            // 随机选择一个机位（1-50）
            int seat = 1 + rand() % 50;

            // 检查该机位在该时段是否已被使用
            if (used_seats[time_idx][seat])
            {
                continue; // 如果已被使用，跳过
            }

            // 标记该机位为已使用
            used_seats[time_idx][seat] = 1;

            // 生成人员信息
            char name[50];
            char phone[12];
            int gender = rand() % 2;

            generate_random_name(name, gender);
            generate_random_phone(phone);

            // 机位状态：如果有人使用，状态为1（占用）
            int seat_status = 1;

            // 写入数据
            fprintf(file, "%04d,%02d,%02d,%s,%s,%d,%s,%d,%d\n", year, month,
                    day, time_slots[time_idx], name, gender, phone, seat,
                    seat_status);

            actual_records++;
            total_records_today++;
        }

        // 如果需要，可以为空闲机位添加记录（状态为0）
        // 这里我们只添加占用机位的记录，空闲机位不单独记录
    }

    return total_records_today;
}

int main()
{
    srand(time(NULL));

    FILE *file = fopen("机房监控数据.csv", "w");
    if (file == NULL)
    {
        printf("无法创建文件！\n");
        return 1;
    }

    // 写入CSV表头
    fprintf(file, "年,月,日,时间,姓名,性别,电话,机位,状态\n");

    // 生成多天数据（例如：2024年1月）
    int start_year  = 2026;
    int start_month = 1;
    int start_day   = 1;
    int num_days    = 100; // 生成7天数据（一周）

    int total_records = 0;

    printf("正在生成机房监控数据...\n");
    printf("机房配置：固定50个机位\n");
    printf("监控时段：08:00-20:00，每2小时一次\n\n");

    for (int day = start_day; day < start_day + num_days; day++)
    {
        int daily_records =
            generate_daily_data(file, start_year, start_month, day);
        total_records += daily_records;

        printf("已生成: %04d年%02d月%02d日 - %d条记录\n", start_year,
               start_month, day, daily_records);
    }

    fclose(file);

    printf("\n=============================================\n");
    printf("数据生成完成！\n");
    printf("总天数: %d天\n", num_days);
    printf("总记录数: %d条\n", total_records);
    printf("保存到: 机房监控数据.csv\n");
    printf("=============================================\n");

    // 显示数据格式示例
    printf("\n数据格式示例：\n");
    printf("年,月,日,时间,姓名,性别,电话,机位,状态\n");
    printf("2024,01,01,08:00,张伟,1,13812345678,15,1\n");
    printf("2024,01,01,10:00,李娜,0,13987654321,32,1\n");

    return 0;
}