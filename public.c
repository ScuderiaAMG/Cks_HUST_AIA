#include "public.h"

/* ************************
function:printline
description:画像素风线函数
create:24/1/31
input:int x,int y,int len,int n,int flag,int COLOR,int wid,int gap
      x,y是第一个小方块左上角起始点，flag=0横着向右，flag=1竖着向左，len记录每个块有多长，n记录有多少格
      wid每格宽度，每格长度为len倍的宽度,gap为每格之间间隙
output:void
************************* */
void printline(int x,int y,int len,int n,int flag,int COLOR,int wid,int gap)
{
   //wid每格宽度，每格长度为len倍的宽度,gap为每格之间间隙
   int t;
   setfillstyle(SOLID_FILL,COLOR);
   while(n)
   {
      t=len;
      while(t){
         bar(x,y,x+wid,y+wid);
         if(flag==0) x+=wid;
         else y+=wid;
         t--;
      }
      n--;
      if(flag==0) x+=gap;
      else y+=gap;
   }

}

void printbox(int x1,int y1,int x2,int y2,int COLOR,int len,int wid,int gap)
{
   int ver,hor,sum,remain_ver,remain_hor;//vertical,horizontal
   sum=wid*len+gap;
   hor=abs(x2-x1)/sum;
   remain_hor=abs(x2-x1)-(hor*sum-gap);
   if(remain_hor<wid*len) remain_hor+=wid*len;
   ver=abs(y2-y1)/sum;
   remain_ver=abs(y2-y1)-(ver*sum-gap);
   if(remain_ver<wid*len) remain_ver+=wid*len;
   printline(x1+remain_hor/2,y1    ,len,hor,0,COLOR,wid,gap);
   printline(x1+remain_hor/2,y2-wid,len,hor,0,COLOR,wid,gap);
   printline(x1,y1+remain_ver/2,len,ver,1,COLOR,wid,gap);
   printline(x2-wid,y1+remain_ver/2,len,ver,1,COLOR,wid,gap);

}

void back_button(int flag)
{
    clrmous(MouseX,MouseY);
    if(flag==PAINT)
    {
        printbox(595,5,630,40,DARKGRAY,1,5,4);
        setcolor(DARKGRAY);
        settextstyle(DEFAULT_FONT   , HORIZ_DIR,3);
        outtextxy(602,10, "x");
    }
    else if(flag==LIGHT)
    {
        printbox(595,5,630,40,BLUE,1,5,4);
        setcolor(BLUE);
        settextstyle(DEFAULT_FONT   , HORIZ_DIR,3);
        outtextxy(602,10, "x");
    }
    else if(flag==RECOVER)
    {
        back_button(PAINT);
    }
    // else if(flag==DELETE)
    // {
    //     setwritemode(XOR_PUT);
    //     back_button(PAINT);
    // }
    else {
        //printf("flag error!");
        delay(3000);
        exit(1);
    }
}
/* 以下为string_limitation函数注释 */
void string_limitation(char* string, int len)  //函数声明，用于限制字符串长度并添加结束符
{
    int i;  //定义循环变量i
    char cpystring[80];  //定义一个长度为80的字符数组，用于临时存储字符串副本
    strcpy(cpystring, string);  //将传入的字符串复制到cpystring数组中
    for (i = 0; i < (len - 1); i++)  //循环从0到len-2，用于遍历并复制字符串的前len-1个字符
    {
        string[i] = cpystring[i];  //将cpystring中的字符逐个复制回原字符串
    }
    string[i + 1] = '~';  //在第len个位置添加'~'字符作为自定义结束符
    string[i + 2] = '\0';  //在第len+1个位置添加'\0'作为标准字符串结束符
}

/* 以下为warning函数注释 */
void warning(char* msg, int nx, int ny, int lettersize)  //函数声明，用于显示警告对话框
{
    int flag = 0;  //定义标志变量flag，用于跟踪鼠标点击状态
    int size;  //定义变量size，用于存储图像缓冲区大小
    void* warning_buffer;  //定义一个指针变量，用于存储警告对话框的图像缓冲区
    int time = 0;  //定义变量time，未在函数中使用
    size = imagesize(180, 220, 460, 300);  //计算指定矩形区域的图像大小
    warning_buffer = malloc(size);  //为图像缓冲区分配内存
    if (warning_buffer != NULL)  //如果内存分配成功
        getimage(180, 220, 460, 300, warning_buffer);  //将指定矩形区域的图像保存到缓冲区中
    else  //如果内存分配失败
    {
        // perror("ERROR IN WARNING!");  //输出错误信息（已注释）
        // delay(3000);  //延迟3秒（已注释）
        // exit(1);  //退出程序（已注释）
    }

    setfillstyle(SOLID_FILL, LIGHTBLUE);  //设置填充样式为实心，颜色为浅蓝色
    bar(180, 220, 460, 300);  //用浅蓝色填充一个矩形区域
    setfillstyle(SOLID_FILL, BLUE);  //设置填充样式为实心，颜色为蓝色
    bar(180, 220, 460, 230);  //用蓝色填充矩形的顶部区域
    bar(180, 220, 190, 300);  //用蓝色填充矩形的左侧区域
    bar(180, 290, 460, 300);  //用蓝色填充矩形的底部区域
    bar(450, 220, 460, 300);  //用蓝色填充矩形的右侧区域
    setcolor(RED);  //设置绘图颜色为红色
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);  //设置线型为实心线，宽度为正常宽度
    line(450, 220, 460, 220);  //绘制红色线条，形成关闭按钮的形状
    line(450, 220, 450, 230);
    line(450, 230, 460, 230);
    line(460, 220, 460, 230);
    line(450, 220, 460, 230);
    line(460, 220, 450, 230);
    setcolor(WHITE);  //将绘图颜色设置为白色
    settextstyle(DEFAULT_FONT, HORIZ_DIR, lettersize);  //设置文本样式为默认字体，水平方向，指定大小
    outtextxy(nx, ny, msg);  //在指定位置输出警告消息

    mouseinit();  //初始化鼠标功能
    while (1)        //无限循环，等待用户操作
    {
        newmouse(&MouseX, &MouseY, &press);  //获取鼠标的新位置和按键状态
        if (mouse_press(450, 220, 460, 230) == 2)  //检测鼠标是否在关闭按钮区域悬停
        {
            if (flag != 1)  //如果标志变量不是1
            {
                flag = 1;  //将标志变量设置为1，表示悬停状态
                MouseS = 1;  //设置鼠标悬停状态变量
            }
        }
        else if (mouse_press(450, 220, 460, 230) == 1)  //检测鼠标是否在关闭按钮区域点击
        {
            clrmous(MouseX, MouseY);  //清除鼠标在该区域的高亮显示
            delay(100);  //延迟100毫秒，防止重复触发
            break;  //退出循环，关闭警告对话框

        }
        else  //如果鼠标不在关闭按钮区域
        {
            if (flag != 0)  //如果标志变量不是0
            {
                MouseS = 0;  //清除鼠标悬停状态变量
                flag = 0;  //将标志变量重置为0
            }
        }
    }
    putimage(180, 220, warning_buffer, COPY_PUT);  //将保存的图像缓冲区恢复到屏幕上
    free(warning_buffer);  //释放图像缓冲区所占用的内存

}

/* 以下为drop_down_menu函数注释 */
void drop_down_menu(int x, int y, int wide, int h, int n, int lettersize, char** msgs, int lightcolor, int darkcolor, char* record)  //函数声明，用于创建下拉菜单
{
    int i;  //定义循环变量i
    int size;  //定义变量size，用于存储图像缓冲区大小
    void* drop_down_buffer;  //定义一个指针变量，用于存储下拉菜单的图像缓冲区
    int flag = n + 1;  //初始化标志变量，
    int place = 0;  //定义变量place，用于跟踪鼠标操作的位置
    int num[10];  //定义一个整型数组，用于存储菜单项的选中状态
    clrmous(MouseX, MouseY);  //清除鼠标在屏幕上的显示
    mouseinit();  //初始化鼠标功能

    if (y + n * h < 470)            //判断下拉菜单是否超出屏幕底部
    {
        size = imagesize(x, y, x + wide, y + n * h + 5);  //计算下拉菜单区域的图像大小
        drop_down_buffer = malloc(size);  //为图像缓冲区分配内存
        if (drop_down_buffer != NULL)  //如果内存分配成功
            getimage(x, y, x + wide, y + n * h + 5, drop_down_buffer);  //将指定区域的图像保存到缓冲区中
        else  //如果内存分配失败
        {
            // perror("ERROR IN REMEMBERING");  //输出错误信息（已注释）
            // delay(3000);  //延迟3秒（已注释）
            // exit(1);  //退出程序（已注释）
        }
        setfillstyle(SOLID_FILL, lightcolor);  //设置填充样式为实心，颜色为lightcolor
        bar(x, y, x + wide, y + n * h);  //用lightcolor填充下拉菜单区域
        setfillstyle(SOLID_FILL, darkcolor);  //设置填充样式为实心，颜色为darkcolor
        bar(x, y, x + 5, y + n * h);  //用darkcolor填充菜单左侧边框
        bar(x + wide - 5, y, x + wide, y + n * h);  //用darkcolor填充菜单右侧边框
        for (i = 0; i <= n; i++)  //循环绘制菜单项之间的分隔线
        {
            bar(x, y + i * h, x + wide, y + i * h + 5);  //用darkcolor绘制分隔线
        }
        settextstyle(DEFAULT_FONT, HORIZ_DIR, lettersize);  //设置文本样式为默认字体，水平方向，指定大小
        for (i = 0; i < n; i++)  //循环输出每个菜单项的文本
        {
            outtextxy(x + 10, y + i * h + 10, msgs[i]);  //在指定位置输出菜单项文本
        }

        while (1)  //无限循环，等待用户操作
        {
            place = 0;  //重置place变量
            newmouse(&MouseX, &MouseY, &press);  //获取鼠标的新位置和按键状态
            for (i = 0; i < n; i++)  //循环检测每个菜单项是否被鼠标操作
            {
                if (mouse_press(x, y + i * h, x + wide, y + (i + 1) * h) == 2)  //检测鼠标是否在菜单项上悬停
                {
                    if (flag != i)  //如果当前菜单项不是之前悬停的项
                    {
                        MouseS = 1;  //设置鼠标悬停状态变量
                        flag = i;  //更新标志变量为当前菜单项索引
                        num[i] = 1;  //标记该菜单项为已悬停
                        clrmous(MouseX, MouseY);  //清除鼠标在该区域的高亮显示
                        setcolor(CYAN);  //设置绘图颜色为青色
                        settextstyle(DEFAULT_FONT, HORIZ_DIR, lettersize);  //设置文本样式
                        outtextxy(x + 10, y + i * h + 10, msgs[i]);  //用青色重新输出菜单项文本，实现高亮效果
                    }
                    place = 1;  //设置place变量为1，表示有鼠标操作
                }
                else if (mouse_press(x, y + i * h, x + wide, y + (i + 1) * h) == 1)  //检测鼠标是否在菜单项上点击
                {
                    strcpy(record, msgs[i]);  //将选中的菜单项文本复制到record变量中
                    clrmous(MouseX, MouseY);  //清除鼠标在该区域的高亮显示
                    putimage(x, y, drop_down_buffer, COPY_PUT);  //将保存的图像缓冲区恢复到屏幕上
                    free(drop_down_buffer);  //释放图像缓冲区所占用的内存
                    place = 2;  //设置place变量为2，表示点击操作完成
                    break;  //退出循环
                }

                if (flag != i && num[i] == 1)  //如果当前菜单项不是标志变量指向的项，但之前被标记为悬停
                {
                    setcolor(DARKGRAY);  //设置绘图颜色为深灰色
                    settextstyle(DEFAULT_FONT, HORIZ_DIR, lettersize);  //设置文本样式
                    outtextxy(x + 10, y + i * h + 10, msgs[i]);  //用深灰色重新输出菜单项文本，取消高亮效果
                }
            }
            if (place == 0)  //如果place变量为0，表示没有鼠标操作
            {
                MouseS = 0;  //清除鼠标悬停状态变量
                flag = n + 1;  //重置标志变量
            }
            else if (place == 2)  //如果place变量为2，表示点击操作完成
            {
                break;  //退出循环
            }
        }
    }
    else  //如果下拉菜单超出屏幕底部，则向上绘制
    {
        size = imagesize(x, y - n * h - 5, x + wide, y);  //计算下拉菜单区域的图像大小
        drop_down_buffer = malloc(size);  //为图像缓冲区分配内存
        if (drop_down_buffer != NULL)  //如果内存分配成功
            getimage(x, y - n * h - 5, x + wide, y, drop_down_buffer);  //将指定区域的图像保存到缓冲区中
        else  //如果内存分配失败
        {
            // perror("ERROR IN REMEMBERING");  //输出错误信息（已注释）
            // delay(3000);  //延迟3秒（已注释）
            // exit(1);  //退出程序（已注释）
        }
        setfillstyle(SOLID_FILL, lightcolor);  //设置填充样式为实心，颜色为lightcolor
        bar(x, y, x + wide, y - n * h);  //用lightcolor填充下拉菜单区域
        setfillstyle(SOLID_FILL, darkcolor);  //设置填充样式为实心，颜色为darkcolor
        bar(x, y, x + 5, y - n * h);  //用darkcolor填充菜单左侧边框
        bar(x + wide - 5, y, x + wide, y - n * h);  //用darkcolor填充菜单右侧边框
        for (i = 0; i <= n; i++)  //循环绘制菜单项之间的分隔线
        {
            bar(x, y - i * h, x + wide, y - i * h - 5);  //用darkcolor绘制分隔线
        }
        settextstyle(DEFAULT_FONT, HORIZ_DIR, lettersize);  //设置文本样式为默认字体，水平方向，指定大小
        for (i = 0; i < n; i++)  //循环输出每个菜单项的文本
        {
            outtextxy(x + 10, y - (i + 1) * h + 10, msgs[i]);  //在指定位置输出菜单项文本
        }
        while (1)  //无限循环，等待用户操作
        {
            place = 0;  //重置place变量
            newmouse(&MouseX, &MouseY, &press);  //获取鼠标的新位置和按键状态
            for (i = 0; i < n; i++)  //循环检测每个菜单项是否被鼠标操作
            {
                if (mouse_press(x, y - (i + 1) * h, x + wide, y - i * h) == 2)  //检测鼠标是否在菜单项上悬停
                {
                    if (flag != i)  //如果当前菜单项不是之前悬停的项
                    {
                        MouseS = 1;  //设置鼠标悬停状态变量
                        flag = i;  //更新标志变量为当前菜单项索引
                        num[i] = 1;  //标记该菜单项为已悬停
                        clrmous(MouseX, MouseY);  //清除鼠标在该区域的高亮显示
                        setcolor(YELLOW);  //设置绘图颜色为黄色
                        settextstyle(DEFAULT_FONT, HORIZ_DIR, lettersize);  //设置文本样式
                        outtextxy(x + 10, y - (i + 1) * h + 10, msgs[i]);  //用黄色重新输出菜单项文本，实现高亮效果
                    }
                    place = 1;  //设置place变量为1，表示有鼠标操作
                }
                else if (mouse_press(x, y - (i + 1) * h, x + wide, y - i * h) == 1)  //检测鼠标是否在菜单项上点击
                {
                    strcpy(record, msgs[i]);  //将选中的菜单项文本复制到record变量中
                    clrmous(MouseX, MouseY);  //清除鼠标在该区域的高亮显示
                    putimage(x, y - n * h - 5, drop_down_buffer, COPY_PUT);  //将保存的图像缓冲区恢复到屏幕上
                    free(drop_down_buffer);  //释放图像缓冲区所占用的内存
                    place = 2;  //设置place变量为2，表示点击操作完成
                    break;  //退出循环
                }

                if (flag != i && num[i] == 1)  //如果当前菜单项不是标志变量指向的项，但之前被标记为悬停
                {
                    setcolor(DARKGRAY);  //设置绘图颜色为深灰色
                    settextstyle(DEFAULT_FONT, HORIZ_DIR, lettersize);  //设置文本样式
                    outtextxy(x + 10, y - (i + 1) * h + 10, msgs[i]);  //用深灰色重新输出菜单项文本，取消高亮效果
                }
            }
            if (place == 0)  //如果place变量为0，表示没有鼠标操作
            {
                MouseS = 0;  //清除鼠标悬停状态变量
                flag = n + 1;  //重置标志变量
            }
            else if (place == 2)  //如果place变量为2，表示点击操作完成
            {
                break;  //退出循环
            }
        }
    }

}