#ifndef _LOGS_H_
#define _LOGS_H_

#define MAX_ITEMS 20
#define BTN_WIDTH 250
#define BTN_HEIGHT 40
#define MAX_FILES 20  // 定义文件数量上限

// 界面绘制与处理函数
int logs_page(int language);
int draw_user_list(const char users[][13], int count, int language, int drawuserlist);
int draw_category_list(int language, int drawcategorylist, int homeflag);
int draw_file_list(const char files[][13], int count, int language, int drawfilelist);
void show_file_content(const char* path, int language, int scuderia);
void trans(int num, char* str);
int go_to_home(int* state);
void draw_home_button(int state);
void put_flower(int x, int y, int pix, int COLOR);
void paint_field_in_log(int record[21][26], char* nowfield, int language, int paintfieldinlog, char* users);
/* 用户数据结构 */
struct UserData
{
    char logsname[9];
    char drone_files[MAX_FILES][13];
    char field_files[MAX_FILES][13];
    char pesticide_files[MAX_FILES][13];
    int drone_count;
    int field_count;
    int pesticide_count;
};

#endif 
