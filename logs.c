#include "logs.h"
#include "public.h"
#include "home.h"
#include "main.h"
#include "draw.h"
#include <dos.h>
#include <conio.h>
#include <dir.h>
#include <fcntl.h>

int logs_page(int language)
{
    FILE* filelog = NULL;
    FILE* fplogs = NULL;
    static int state = SELECT_USER;                 // 当前界面状�?
    static char currentUser[13] = { 0 };            // 当前选中用户
    static char currentCategory[13] = { 0 };        // 当前选中类别
    static char currentFile[13] = { 0 };            // 当前选中文件

    int drawuserlist = 0;                    // �?否绘制用户列�?
    int drawcategorylist = 0;                // �?否绘制类�?列表
    int drawfilelist = 0;                    // �?否绘制文件列�?
    int drawcontent = 0;                     // �?否绘制文件内�?

    int new_state = 0;
    int showHomeButton = 0;
    struct ffblk ffblk;
    char path[128];
    int done;
    int returnflag = 0;
    int selected;
    int userCount = 0;
    int fileCount = 0;
    char users[MAX_ITEMS][13] = { 0 };
    char files[MAX_ITEMS][13] = { 0 };

    int record[21][26] = { 0 };                // 农田记录数组
    char* nowfield;                            // 当前农田名称

	int logsflag = 0;                            // 用于记录类别选择
	//int paintfieldinlog = 0;                     // 用于绘制农田界面


    const char* categories[] = { "DRONE", "FIELD", "PESTICIDE" };

    delay(50);
	//memset(record, 0, sizeof(record)); // 农田记录数组刨l?�
    clrmous(MouseX, MouseY);
    cleardevice();      // �?保清屏生�?
    setbkcolor(WHITE);  // 显式设置背景�?
    mouseinit();


    // 主循�?
    while (1)
    {
        newmouse(&MouseX, &MouseY, &press);

        if (showHomeButton) {
            go_to_home(&state);
            if (state == SELECT_USER) {
                // 重置所有静态变量和界面状�?
                currentUser[0] = '\0';
                currentCategory[0] = '\0';
                currentFile[0] = '\0';
                drawuserlist = 0;
                drawcategorylist = 0;
                drawfilelist = 0;
                drawcontent = 0;
                showHomeButton = 0; // 隐藏返回主页按钮
                return HOME;
            }
        }
        switch (state)
        {
            case SELECT_USER:
        {
            // �?描目录获取用户列�?
            done = findfirst("C:\\DATA\\*.*", &ffblk, FA_DIREC);

            userCount = 0; // 重置用户计数

            delay(50);
            while (!done && userCount < MAX_ITEMS)
            {
                if ((ffblk.ff_attrib & FA_DIREC) && strcmp(ffblk.ff_name, ".") && strcmp(ffblk.ff_name, ".."))
                {
                    strcpy(users[userCount++], ffblk.ff_name);
                }
                done = findnext(&ffblk);
            }

            // 绘制用户列表并获取选择
            selected = draw_user_list(users, userCount, language, drawuserlist);
            if (drawuserlist == 0)
            {
                drawuserlist = 1;
            }


            if (selected != -1)
            {
                strncpy(currentUser, users[selected], sizeof(currentUser) - 1);
                currentUser[sizeof(currentUser) - 1] = '\0'; // �?保终止�??
                delay(50);
                state = SELECT_CATEGORY;
            }
            break;
        }

            case SELECT_CATEGORY:
        {

            // 绘制固定三个类别
            selected = draw_category_list(language, drawcategorylist, state);

            logsflag = selected;

            if (drawcategorylist == 0)
            {

                drawcategorylist = 1;
            }

            if (selected != -1)
            {
                strcpy(currentCategory, categories[selected]);
                delay(50);
                state = SELECT_FILE;
            }
            break;
        }

            case SELECT_FILE:
        {

            // 构建�?径：C:\DATA\用户\类别\*.dat
            sprintf(path, "C:\\DATA\\%s\\%s\\*.dat", currentUser, currentCategory);

            done = findfirst(path, &ffblk, 0);

            if (drawfilelist == 0)
            {
                while (!done && fileCount < MAX_ITEMS)
                {
                    strcpy(files[fileCount++], ffblk.ff_name);
                    done = findnext(&ffblk);
                }
            }

            

            // 绘制文件列表
            selected = draw_file_list(files, fileCount, language, drawfilelist);
            if (drawfilelist == 0)
            {

                drawfilelist = 1;
            }

            if (selected != -1)
            {
                strcpy(currentFile, files[selected]);
                delay(50);
                state = SHOW_CONTENT;
            }

            break;
        }

        
            case SHOW_CONTENT:
        {

            // 构建完整文件�?�?
            sprintf(path, "C:\\DATA\\%s\\%s\\%s", currentUser, currentCategory, currentFile);

            nowfield = currentFile;              // 当前农田名称
            if (drawcontent == 0)
            {
                if (logsflag == 1) // 如果�?农田
                {
                    paint_field_in_log(record, nowfield, language, drawcontent, currentUser);   // 绘制农田界面
                }
                else
                {
                    show_file_content(path, language, drawcontent);
                }
                drawcontent = 1;
            }
            //if(logsflag == 1) // 如果�?农田
            //{
            //    paint_field(record, nowfield, language);   // 绘制农田界面
            //}
            //else
            //{
            //    show_file_content(path, language, drawcontent);
            //}
            //paint_field(record, nowfield, language);   // 绘制农田界面

            //show_file_content(path, language, drawcontent);

            if(drawcontent == 0)
            {
                drawcontent = 1;
			}
            showHomeButton = 1;

            delay(50);
            break;
        }
        }

    }
}

int draw_user_list(const char users[][13], int count, int language, int drawuserlist)
{

    int i, y;


    if (drawuserlist == 0)
    {
        cleardevice();
        clrmous(MouseX, MouseY);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
        put_flower(400, 240, 15, BLUE);
		put_flower(460, 300, 5, GREEN);
        if (language == ENGLISH)
        {
            setcolor(BLUE);
            outtextxy(50, 30, "Select User:");
        }
        else if (language == CHINESE)
        {
            puthz(50, 30, "ѡ���û�", 32, 32, BLUE);
        }

        // 绘制用户列表

        for (i = 0; i < count; i++)
        {
            y = 80 + i * 40;
            printbox(50, y, 50 + BTN_WIDTH, y + BTN_HEIGHT, DARKGRAY, 1, 4, 5);
            outtextxy(60, y + 8, users[i]);
        }
        drawuserlist++;

    }



    // 检测点�?
    for (i = 0; i < count; i++)
    {
        y = 80 + i * 40;
        if (MouseX > 50 && MouseX < 50 + BTN_WIDTH && MouseY > y && MouseY < y + BTN_HEIGHT && mouse_press(50, y, 50 + BTN_WIDTH, y + BTN_HEIGHT) == 2)
        {
            setcolor(CYAN);
            printbox(50, y, 50 + BTN_WIDTH, y + BTN_HEIGHT, YELLOW, 1, 4, 5);
            outtextxy(60, y + 8, users[i]);
        }

        if (mouse_press(50, y, 50 + BTN_WIDTH, y + BTN_HEIGHT) == 0)
        {
            setcolor(BLUE);
            printbox(50, y, 50 + BTN_WIDTH, y + BTN_HEIGHT, DARKGRAY, 1, 4, 5);
            outtextxy(60, y + 8, users[i]);
        }
        
        if (MouseX > 50 && MouseX < 50 + BTN_WIDTH && MouseY > y && MouseY < y + BTN_HEIGHT && mouse_press(50, y, 50 + BTN_WIDTH, y + BTN_HEIGHT) == 1)
        {
            return i;
        }
    }
    return -1;

    
}

int draw_category_list(int language, int drawcategorylist, int homeflag)
{
    const char* categories[] = { "DRONE", "FIELD", "PESTICIDE" };
    int i, y;

    if (drawcategorylist == 0)
    {
        cleardevice();
        clrmous(MouseX, MouseY);
        setfillstyle(SOLID_FILL, WHITE);
        bar(50, 70, 330, 480);
        put_flower(150, 280, 20, RED);
		put_flower(200, 340, 10, CYAN);
        if (language == ENGLISH)
        {
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
            setcolor(BLUE);
            outtextxy(50, 30, "Select Category:");
        }
        else if (language == CHINESE)
        {
            puthz(50, 30, "ѡ�����", 32, 32, BLUE);
        }

        for (i = 0; i < 3; i++)
        {
            y = 80 + i * 40;
            printbox(350, y, 350 + BTN_WIDTH, y + BTN_HEIGHT, DARKGRAY, 1, 5, 4);
            outtextxy(360, y + 8, categories[i]);
        }
        drawcategorylist++;
    }


    // 检测点�?
    for (i = 0; i < 3; i++)
    {
        y = 80 + i * 40;

        if (MouseX > 350 && MouseX < 350 + BTN_WIDTH && MouseY > y && MouseY < y + BTN_HEIGHT && mouse_press(350, y, 350 + BTN_WIDTH, y + BTN_HEIGHT) == 2)
        {
            setcolor(CYAN);
            printbox(350, y, 350 + BTN_WIDTH, y + BTN_HEIGHT, YELLOW, 1, 4, 5);
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
            outtextxy(360, y + 8, categories[i]);
        }
        if (mouse_press(350, y, 350 + BTN_WIDTH, y + BTN_HEIGHT) == 0)
        {
            setcolor(BLUE);
            printbox(350, y, 350 + BTN_WIDTH, y + BTN_HEIGHT, DARKGRAY, 1, 4, 5);
            outtextxy(360, y + 8, categories[i]);
        }
        if (MouseX > 350 && MouseX < 350 + BTN_WIDTH && MouseY > y && MouseY < y + BTN_HEIGHT && mouse_press(350, y, 350 + BTN_WIDTH, y + BTN_HEIGHT) == 1)
        {
            return i;
        }
    }
    return -1;
}

int draw_file_list(const char files[][13], int count, int language, int drawfilelist)
{
    int i, y = 0;
    static int tag=0;
    if (drawfilelist == 0)
    {
        clrmous(MouseX, MouseY);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
        cleardevice();
		put_flower(450, 290, 25, BLUE);
		put_flower(490, 360, 5, RED);
        // 绘制标�??
        if (language == ENGLISH)
        {
            setcolor(BLUE);
            outtextxy(50, 30, "Select File:");
        }
        else if (language == CHINESE)
        {
            puthz(50, 30, "ѡ���ļ�", 32, 32, BLUE);
        }
        // 绘制文件列表

        for (i = 0; i < count; i++)
        {
            y = 80 + i * 40;
            printbox(50, y, 50 + BTN_WIDTH, y + BTN_HEIGHT, DARKGRAY, 1, 5, 4);
            outtextxy(60, y + 8, files[i]);
        }
        drawfilelist++;
    }
    // 检测点�?
    for (i = 0; i < count; i++)
    {
        y = 80 + i * 40;
        if (MouseX > 50 && MouseX < 50 + BTN_WIDTH && MouseY > y && MouseY < y + BTN_HEIGHT && mouse_press(50, y, 50 + BTN_WIDTH, y + BTN_HEIGHT) == 2)
        {
            setcolor(CYAN);
            printbox(50, y, 50 + BTN_WIDTH, y + BTN_HEIGHT, YELLOW, 1, 4, 5);
            outtextxy(60, y + 8, files[i]);
        }
        
        if (MouseX > 50 && MouseX < 50 + BTN_WIDTH && MouseY > y && MouseY < y + BTN_HEIGHT && mouse_press(50, y, 50 + BTN_WIDTH, y + BTN_HEIGHT) == 1)
        {
           
            return i;
        }

        if (mouse_press(50, y, 50 + BTN_WIDTH, y + BTN_HEIGHT) == 0)
        {
            setcolor(BLUE);
            printbox(50, y, 50 + BTN_WIDTH, y + BTN_HEIGHT, DARKGRAY, 1, 4, 5);
            outtextxy(60, y + 8, files[i]);
        }
    }
    return -1;
}

void show_file_content(const char* path, int language, int drawcontent)
{
    FILE* fp = fopen(path, "rb");
    char buffer[16];
    int y = 70;

    if (drawcontent == 0)
    {
        clrmous(MouseX, MouseY);
        cleardevice();
        //settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 3);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
        printbox(595, 5, 630, 40, DARKGRAY, 1, 5, 4);
        setcolor(DARKGRAY);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
        outtextxy(602, 10, "x");
        if (language == ENGLISH)
        {
            setcolor(BLUE);
            outtextxy(50, 50, "Existing:");
        }
        else if(language== CHINESE)
        {
            puthz(50, 50, "�Ѵ��ڵ�", 32, 32, BLUE);
		}

      
        if (!fp)
        {

            if (language == ENGLISH)
            {
                setcolor(BLUE);
                outtextxy(50, 80, "Empty file!");
                outtextxy(50, 110, "Not Found!");
            }
            else if (language == CHINESE)
            {
                puthz(50, 80, "���ļ�Ϊ��", 32, 32, BLUE);
                puthz(50, 110, "δ�ҵ�", 32, 32, BLUE);
            }
            //return;
            drawcontent++;
        }
        settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 3);
        // 读取,显示内�??
        while (fgets(buffer, sizeof(buffer), fp))
        {
            setcolor(BLUE);
            outtextxy(80, y + 30, buffer);
            y += 30;
            if (y > 300)
                break; // 超出屏幕就停�?
        }
    }
    drawcontent++;
    
    fclose(fp);
}

void trans(int num, char* str)
{
    int temp = num;
    int digits = 0; //位数
    int index = 0;
    while (temp != 0)
    {
        temp /= 10;
        digits++;
    }
    index = digits - 1;
    temp = num;
    do
    {
        str[index--] = temp % 10 + '0';
        temp /= 10;
    } while (temp != 0);
    //最后加0
    str[digits] = '\0';
    //�?0也输出字符串
    if (num == 0)
    {
        str[0] = '0';
        str[1] = '\0';
    }
}
int go_to_home(int* state) 
{
    static int button_state = 0; // 0: 正常, 1: �?�?, 2: 按下
    int new_button_state = button_state;

    // 检测鼠标是否在按钮�?
    if (MouseX >= 595 && MouseX <= 630 && MouseY >= 5 && MouseY <= 40) {
        if (press == 1) 
        { // 鼠标按下
            new_button_state = 2;
            *state = SELECT_USER;
        }
        else
        { // 鼠标�?�?
            new_button_state = 1;
        }
    }
    else {
        new_button_state = 0;
    }

    // 如果按钮状态发生变化，则重绘按�?
    if (new_button_state != button_state) {
        button_state = new_button_state;
        draw_home_button(button_state);
    }

    return button_state;
}

void draw_home_button(int state) 
{
    //cleardevice();
    switch (state) 
    {
    case 0: // 正常状�?
        printbox(595, 5, 630, 40, DARKGRAY, 1, 5, 4);
        setcolor(DARKGRAY);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
        outtextxy(602, 10, "x");
        break;
    case 1: // �?停状�?
        printbox(595, 5, 630, 40, BLUE, 1, 5, 4);
        setcolor(BLUE);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
        outtextxy(602, 10, "x");
        break;
    case 2: // 按下状�?
        printbox(595, 5, 630, 40, DARKGRAY, 1, 5, 4);
        setcolor(DARKGRAY);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
        outtextxy(602, 10, "x");
        break;
    }
}

// 绘制一朵像素�?�格的花朵（�?�? + 花瓣 + 茎）
void put_flower(int x, int y, int pix, int COLOR)
{
    // 主干
    printline(x, y - pix * 9, 1, 9, 1, COLOR, pix, 0);

    // �?向花瓣（�?间两层）
    printline(x - 2 * pix, y - pix * 6, 1, 5, 0, COLOR, pix, 0);
    printline(x - 2 * pix, y - pix * 5, 1, 5, 0, COLOR, pix, 0);

    // 左上与右上花�?
    printline(x - 2 * pix, y - pix * 10, 1, 4, 1, COLOR, pix, 0);
    printline(x - 3 * pix, y - pix * 9, 1, 3, 1, COLOR, pix, 0);
    printline(x + 2 * pix, y - pix * 10, 1, 4, 1, COLOR, pix, 0);
    printline(x + 3 * pix, y - pix * 9, 1, 3, 1, COLOR, pix, 0);

    // �?间加�?
    printline(x, y - pix * 8, 1, 3, 0, COLOR, pix, 0);

    // 左右下方花瓣
    printline(x - 4 * pix, y - pix * 4, 1, 2, 1, COLOR, pix, 0);
    printline(x - 3 * pix, y - pix * 3, 1, 2, 1, COLOR, pix, 0);
    printline(x + 4 * pix, y - pix * 4, 1, 2, 1, COLOR, pix, 0);
    printline(x + 3 * pix, y - pix * 3, 1, 2, 1, COLOR, pix, 0);

    // 下层�?向花�?
    printline(x - 2 * pix, y - pix * 2, 1, 5, 0, COLOR, pix, 0);
    printline(x - 2 * pix, y - pix * 1, 1, 5, 0, COLOR, pix, 0);

    // 左下垂直线补花芯
    printline(x - pix, y - pix * 7, 1, 3, 1, COLOR, pix, 0);
}

void paint_field_in_log(int record[21][26], char* nowfield, int language, int paintfieldinlog, char* users)
{
    int i, j, x, y;
    char path[100]; 
    FILE* fp;       
    char string[80] = "c:\\DATA\\";
    char* username = users;
   
	memset(record, 0, sizeof(record)); 
    
    
    if (username == NULL) 
    {
		cleardevice();
        setbkcolor(BLACK);
        printf("�޷���ȡ�û�����\n");
        delay(1000);
        return;
    }
    clrmous(MouseX, MouseY); 
    if (strlen(nowfield) != 0)
    {
        strcat(string, username);
        strcat(string, "\\");
        strcat(string, "FIELD\\");
        strcat(string, nowfield);
        //strcat(string, ".dat");
        if ((fp = fopen(string, "rb")) != NULL)
        {

            for (i = 0; i < 21; i++)
            {
                fread(record[i], sizeof(int), 26, fp);
            }
        }
        else
        {
            cleardevice();
            
            setbkcolor(BLACK);
			printf("�޷����ļ�: %s\n", path);   
            delay(1000);
        }
        fclose(fp);
        
    }
    
    delay(50);
    setbkcolor(WHITE); // 譜崔嘘尚弼葎易弼
    cleardevice();     // 賠茅譜姥

    

    back_button(PAINT); // 紙崙卦指梓泥
    setcolor(DARKGRAY);  // 譜崔冲弼葎圧子弼
    
    if (language == ENGLISH)
    {
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 4); // 譜崔猟云劔�?�
        outtextxy(110, 10, "NAME:"); // 補竃猟云 NAME:
    }
    else if (language == CHINESE)
    {
        puthz(110, 8, "����", 32, 32, DARKGRAY); // 補竃査忖 兆各
    }
    outtextxy(260, 10, nowfield); // 補竃輝念滴弥兆各

    setlinestyle(SOLID_LINE, 0, THICK_WIDTH); // 譜崔㞍侏葎糞�?
    setcolor(DARKGRAY); // 譜崔冲弼葎圧子弼
    line(110, 50, 110, 470); // 紙崙換岷�?
    line(110, 470, 630, 470); // 紙崙邦峠�?
    line(110, 50, 108, 60); // 紙崙眉叔侘恣貧叔
    line(110, 50, 112, 60);
    line(630, 470, 620, 468); // 紙崙眉叔侘嘔和叔
    line(630, 470, 620, 472);

    setlinestyle(DOTTED_LINE, 0, NORM_WIDTH); // 譜崔㞍侏葎倡㞍
    setcolor(DARKGRAY); // 譜崔冲弼葎圧子弼
    for (i = 0; i < 26; i++) // 紙崙換岷倡㞍
    {
        line(110 + i * 20, 50, 110 + i * 20, 470);
    }
    for (i = 0; i < 21; i++) // 紙崙邦峠倡㞍
    {
        line(110, 470 - i * 20, 630, 470 - i * 20);
    }

    // 紙崙滴弥�?�?
    for (i = 0; i < 21; i++)//y
    {
        for (j = 0; j < 26; j++)//x
        {
            x = 110 + j * 20;
            y = 470 - i * 20 - 20;
            if (record[i][j] != 2 && record[i][j] != 0)
            {
                setfillstyle(SOLID_FILL, DARKGRAY);
                bar(110 + j * 20, 470 - (i + 1) * 20, 110 + (j + 1) * 20, 470 - i * 20);
            }
            if (record[i][j] == 2)
            {
                setfillstyle(SOLID_FILL, LIGHTBLUE);
                bar(110 + j * 20, 470 - (i + 1) * 20, 110 + (j + 1) * 20, 470 - i * 20);
            }
            if (record[i][j] == 3)
            {
                put_house(x, y, BROWN, CYAN, 2);
            }
            else if (record[i][j] == 4)
            {
                put_house(x, y, BROWN, MAGENTA, 2);
            }
            else if (record[i][j] == 5)
            {
                put_house(x, y, BROWN, YELLOW, 2);
            }
            else if (record[i][j] == 6)
            {
                put_house(x, y, BROWN, BLUE, 2);
            }
            else if (record[i][j] >= 10 && record[i][j] <= 39) {
                put_crop1(x, y, SPROUT, HEALTHY);
            }
            else if (record[i][j] >= 40 && record[i][j] <= 69) {
                put_crop2(x, y, SPROUT, HEALTHY);
            }
            else if (record[i][j] >= 70 && record[i][j] <= 99) {
                put_crop3(x, y, SPROUT, HEALTHY);
            }
        }
    }

    paintfieldinlog++;
}
