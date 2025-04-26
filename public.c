#include "public.h"

/* ************************
function:printline
description:�����ط��ߺ���
create:24/1/31
input:int x,int y,int len,int n,int flag,int COLOR,int wid,int gap
      x,y�ǵ�һ��С�������Ͻ���ʼ�㣬flag=0�������ң�flag=1��������len��¼ÿ�����ж೤��n��¼�ж��ٸ�
      widÿ���ȣ�ÿ�񳤶�Ϊlen���Ŀ��,gapΪÿ��֮���϶
output:void
************************* */
void printline(int x,int y,int len,int n,int flag,int COLOR,int wid,int gap)
{
   //widÿ���ȣ�ÿ�񳤶�Ϊlen���Ŀ��,gapΪÿ��֮���϶
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
/* ����Ϊstring_limitation����ע�� */
void string_limitation(char* string, int len)  //�������������������ַ������Ȳ���ӽ�����
{
    int i;  //����ѭ������i
    char cpystring[80];  //����һ������Ϊ80���ַ����飬������ʱ�洢�ַ�������
    strcpy(cpystring, string);  //��������ַ������Ƶ�cpystring������
    for (i = 0; i < (len - 1); i++)  //ѭ����0��len-2�����ڱ����������ַ�����ǰlen-1���ַ�
    {
        string[i] = cpystring[i];  //��cpystring�е��ַ�������ƻ�ԭ�ַ���
    }
    string[i + 1] = '~';  //�ڵ�len��λ�����'~'�ַ���Ϊ�Զ��������
    string[i + 2] = '\0';  //�ڵ�len+1��λ�����'\0'��Ϊ��׼�ַ���������
}

/* ����Ϊwarning����ע�� */
void warning(char* msg, int nx, int ny, int lettersize)  //����������������ʾ����Ի���
{
    int flag = 0;  //�����־����flag�����ڸ��������״̬
    int size;  //�������size�����ڴ洢ͼ�񻺳�����С
    void* warning_buffer;  //����һ��ָ����������ڴ洢����Ի����ͼ�񻺳���
    int time = 0;  //�������time��δ�ں�����ʹ��
    size = imagesize(180, 220, 460, 300);  //����ָ�����������ͼ���С
    warning_buffer = malloc(size);  //Ϊͼ�񻺳��������ڴ�
    if (warning_buffer != NULL)  //����ڴ����ɹ�
        getimage(180, 220, 460, 300, warning_buffer);  //��ָ�����������ͼ�񱣴浽��������
    else  //����ڴ����ʧ��
    {
        // perror("ERROR IN WARNING!");  //���������Ϣ����ע�ͣ�
        // delay(3000);  //�ӳ�3�루��ע�ͣ�
        // exit(1);  //�˳�������ע�ͣ�
    }

    setfillstyle(SOLID_FILL, LIGHTBLUE);  //���������ʽΪʵ�ģ���ɫΪǳ��ɫ
    bar(180, 220, 460, 300);  //��ǳ��ɫ���һ����������
    setfillstyle(SOLID_FILL, BLUE);  //���������ʽΪʵ�ģ���ɫΪ��ɫ
    bar(180, 220, 460, 230);  //����ɫ�����εĶ�������
    bar(180, 220, 190, 300);  //����ɫ�����ε��������
    bar(180, 290, 460, 300);  //����ɫ�����εĵײ�����
    bar(450, 220, 460, 300);  //����ɫ�����ε��Ҳ�����
    setcolor(RED);  //���û�ͼ��ɫΪ��ɫ
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);  //��������Ϊʵ���ߣ����Ϊ�������
    line(450, 220, 460, 220);  //���ƺ�ɫ�������γɹرհ�ť����״
    line(450, 220, 450, 230);
    line(450, 230, 460, 230);
    line(460, 220, 460, 230);
    line(450, 220, 460, 230);
    line(460, 220, 450, 230);
    setcolor(WHITE);  //����ͼ��ɫ����Ϊ��ɫ
    settextstyle(DEFAULT_FONT, HORIZ_DIR, lettersize);  //�����ı���ʽΪĬ�����壬ˮƽ����ָ����С
    outtextxy(nx, ny, msg);  //��ָ��λ�����������Ϣ

    mouseinit();  //��ʼ����깦��
    while (1)        //����ѭ�����ȴ��û�����
    {
        newmouse(&MouseX, &MouseY, &press);  //��ȡ������λ�úͰ���״̬
        if (mouse_press(450, 220, 460, 230) == 2)  //�������Ƿ��ڹرհ�ť������ͣ
        {
            if (flag != 1)  //�����־��������1
            {
                flag = 1;  //����־��������Ϊ1����ʾ��ͣ״̬
                MouseS = 1;  //���������ͣ״̬����
            }
        }
        else if (mouse_press(450, 220, 460, 230) == 1)  //�������Ƿ��ڹرհ�ť������
        {
            clrmous(MouseX, MouseY);  //�������ڸ�����ĸ�����ʾ
            delay(100);  //�ӳ�100���룬��ֹ�ظ�����
            break;  //�˳�ѭ�����رվ���Ի���

        }
        else  //�����겻�ڹرհ�ť����
        {
            if (flag != 0)  //�����־��������0
            {
                MouseS = 0;  //��������ͣ״̬����
                flag = 0;  //����־��������Ϊ0
            }
        }
    }
    putimage(180, 220, warning_buffer, COPY_PUT);  //�������ͼ�񻺳����ָ�����Ļ��
    free(warning_buffer);  //�ͷ�ͼ�񻺳�����ռ�õ��ڴ�

}

/* ����Ϊdrop_down_menu����ע�� */
void drop_down_menu(int x, int y, int wide, int h, int n, int lettersize, char** msgs, int lightcolor, int darkcolor, char* record)  //�������������ڴ��������˵�
{
    int i;  //����ѭ������i
    int size;  //�������size�����ڴ洢ͼ�񻺳�����С
    void* drop_down_buffer;  //����һ��ָ����������ڴ洢�����˵���ͼ�񻺳���
    int flag = n + 1;  //��ʼ����־������
    int place = 0;  //�������place�����ڸ�����������λ��
    int num[10];  //����һ���������飬���ڴ洢�˵����ѡ��״̬
    clrmous(MouseX, MouseY);  //����������Ļ�ϵ���ʾ
    mouseinit();  //��ʼ����깦��

    if (y + n * h < 470)            //�ж������˵��Ƿ񳬳���Ļ�ײ�
    {
        size = imagesize(x, y, x + wide, y + n * h + 5);  //���������˵������ͼ���С
        drop_down_buffer = malloc(size);  //Ϊͼ�񻺳��������ڴ�
        if (drop_down_buffer != NULL)  //����ڴ����ɹ�
            getimage(x, y, x + wide, y + n * h + 5, drop_down_buffer);  //��ָ�������ͼ�񱣴浽��������
        else  //����ڴ����ʧ��
        {
            // perror("ERROR IN REMEMBERING");  //���������Ϣ����ע�ͣ�
            // delay(3000);  //�ӳ�3�루��ע�ͣ�
            // exit(1);  //�˳�������ע�ͣ�
        }
        setfillstyle(SOLID_FILL, lightcolor);  //���������ʽΪʵ�ģ���ɫΪlightcolor
        bar(x, y, x + wide, y + n * h);  //��lightcolor��������˵�����
        setfillstyle(SOLID_FILL, darkcolor);  //���������ʽΪʵ�ģ���ɫΪdarkcolor
        bar(x, y, x + 5, y + n * h);  //��darkcolor���˵����߿�
        bar(x + wide - 5, y, x + wide, y + n * h);  //��darkcolor���˵��Ҳ�߿�
        for (i = 0; i <= n; i++)  //ѭ�����Ʋ˵���֮��ķָ���
        {
            bar(x, y + i * h, x + wide, y + i * h + 5);  //��darkcolor���Ʒָ���
        }
        settextstyle(DEFAULT_FONT, HORIZ_DIR, lettersize);  //�����ı���ʽΪĬ�����壬ˮƽ����ָ����С
        for (i = 0; i < n; i++)  //ѭ�����ÿ���˵�����ı�
        {
            outtextxy(x + 10, y + i * h + 10, msgs[i]);  //��ָ��λ������˵����ı�
        }

        while (1)  //����ѭ�����ȴ��û�����
        {
            place = 0;  //����place����
            newmouse(&MouseX, &MouseY, &press);  //��ȡ������λ�úͰ���״̬
            for (i = 0; i < n; i++)  //ѭ�����ÿ���˵����Ƿ�������
            {
                if (mouse_press(x, y + i * h, x + wide, y + (i + 1) * h) == 2)  //�������Ƿ��ڲ˵�������ͣ
                {
                    if (flag != i)  //�����ǰ�˵����֮ǰ��ͣ����
                    {
                        MouseS = 1;  //���������ͣ״̬����
                        flag = i;  //���±�־����Ϊ��ǰ�˵�������
                        num[i] = 1;  //��Ǹò˵���Ϊ����ͣ
                        clrmous(MouseX, MouseY);  //�������ڸ�����ĸ�����ʾ
                        setcolor(CYAN);  //���û�ͼ��ɫΪ��ɫ
                        settextstyle(DEFAULT_FONT, HORIZ_DIR, lettersize);  //�����ı���ʽ
                        outtextxy(x + 10, y + i * h + 10, msgs[i]);  //����ɫ��������˵����ı���ʵ�ָ���Ч��
                    }
                    place = 1;  //����place����Ϊ1����ʾ��������
                }
                else if (mouse_press(x, y + i * h, x + wide, y + (i + 1) * h) == 1)  //�������Ƿ��ڲ˵����ϵ��
                {
                    strcpy(record, msgs[i]);  //��ѡ�еĲ˵����ı����Ƶ�record������
                    clrmous(MouseX, MouseY);  //�������ڸ�����ĸ�����ʾ
                    putimage(x, y, drop_down_buffer, COPY_PUT);  //�������ͼ�񻺳����ָ�����Ļ��
                    free(drop_down_buffer);  //�ͷ�ͼ�񻺳�����ռ�õ��ڴ�
                    place = 2;  //����place����Ϊ2����ʾ����������
                    break;  //�˳�ѭ��
                }

                if (flag != i && num[i] == 1)  //�����ǰ�˵���Ǳ�־����ָ������֮ǰ�����Ϊ��ͣ
                {
                    setcolor(DARKGRAY);  //���û�ͼ��ɫΪ���ɫ
                    settextstyle(DEFAULT_FONT, HORIZ_DIR, lettersize);  //�����ı���ʽ
                    outtextxy(x + 10, y + i * h + 10, msgs[i]);  //�����ɫ��������˵����ı���ȡ������Ч��
                }
            }
            if (place == 0)  //���place����Ϊ0����ʾû��������
            {
                MouseS = 0;  //��������ͣ״̬����
                flag = n + 1;  //���ñ�־����
            }
            else if (place == 2)  //���place����Ϊ2����ʾ����������
            {
                break;  //�˳�ѭ��
            }
        }
    }
    else  //��������˵�������Ļ�ײ��������ϻ���
    {
        size = imagesize(x, y - n * h - 5, x + wide, y);  //���������˵������ͼ���С
        drop_down_buffer = malloc(size);  //Ϊͼ�񻺳��������ڴ�
        if (drop_down_buffer != NULL)  //����ڴ����ɹ�
            getimage(x, y - n * h - 5, x + wide, y, drop_down_buffer);  //��ָ�������ͼ�񱣴浽��������
        else  //����ڴ����ʧ��
        {
            // perror("ERROR IN REMEMBERING");  //���������Ϣ����ע�ͣ�
            // delay(3000);  //�ӳ�3�루��ע�ͣ�
            // exit(1);  //�˳�������ע�ͣ�
        }
        setfillstyle(SOLID_FILL, lightcolor);  //���������ʽΪʵ�ģ���ɫΪlightcolor
        bar(x, y, x + wide, y - n * h);  //��lightcolor��������˵�����
        setfillstyle(SOLID_FILL, darkcolor);  //���������ʽΪʵ�ģ���ɫΪdarkcolor
        bar(x, y, x + 5, y - n * h);  //��darkcolor���˵����߿�
        bar(x + wide - 5, y, x + wide, y - n * h);  //��darkcolor���˵��Ҳ�߿�
        for (i = 0; i <= n; i++)  //ѭ�����Ʋ˵���֮��ķָ���
        {
            bar(x, y - i * h, x + wide, y - i * h - 5);  //��darkcolor���Ʒָ���
        }
        settextstyle(DEFAULT_FONT, HORIZ_DIR, lettersize);  //�����ı���ʽΪĬ�����壬ˮƽ����ָ����С
        for (i = 0; i < n; i++)  //ѭ�����ÿ���˵�����ı�
        {
            outtextxy(x + 10, y - (i + 1) * h + 10, msgs[i]);  //��ָ��λ������˵����ı�
        }
        while (1)  //����ѭ�����ȴ��û�����
        {
            place = 0;  //����place����
            newmouse(&MouseX, &MouseY, &press);  //��ȡ������λ�úͰ���״̬
            for (i = 0; i < n; i++)  //ѭ�����ÿ���˵����Ƿ�������
            {
                if (mouse_press(x, y - (i + 1) * h, x + wide, y - i * h) == 2)  //�������Ƿ��ڲ˵�������ͣ
                {
                    if (flag != i)  //�����ǰ�˵����֮ǰ��ͣ����
                    {
                        MouseS = 1;  //���������ͣ״̬����
                        flag = i;  //���±�־����Ϊ��ǰ�˵�������
                        num[i] = 1;  //��Ǹò˵���Ϊ����ͣ
                        clrmous(MouseX, MouseY);  //�������ڸ�����ĸ�����ʾ
                        setcolor(YELLOW);  //���û�ͼ��ɫΪ��ɫ
                        settextstyle(DEFAULT_FONT, HORIZ_DIR, lettersize);  //�����ı���ʽ
                        outtextxy(x + 10, y - (i + 1) * h + 10, msgs[i]);  //�û�ɫ��������˵����ı���ʵ�ָ���Ч��
                    }
                    place = 1;  //����place����Ϊ1����ʾ��������
                }
                else if (mouse_press(x, y - (i + 1) * h, x + wide, y - i * h) == 1)  //�������Ƿ��ڲ˵����ϵ��
                {
                    strcpy(record, msgs[i]);  //��ѡ�еĲ˵����ı����Ƶ�record������
                    clrmous(MouseX, MouseY);  //�������ڸ�����ĸ�����ʾ
                    putimage(x, y - n * h - 5, drop_down_buffer, COPY_PUT);  //�������ͼ�񻺳����ָ�����Ļ��
                    free(drop_down_buffer);  //�ͷ�ͼ�񻺳�����ռ�õ��ڴ�
                    place = 2;  //����place����Ϊ2����ʾ����������
                    break;  //�˳�ѭ��
                }

                if (flag != i && num[i] == 1)  //�����ǰ�˵���Ǳ�־����ָ������֮ǰ�����Ϊ��ͣ
                {
                    setcolor(DARKGRAY);  //���û�ͼ��ɫΪ���ɫ
                    settextstyle(DEFAULT_FONT, HORIZ_DIR, lettersize);  //�����ı���ʽ
                    outtextxy(x + 10, y - (i + 1) * h + 10, msgs[i]);  //�����ɫ��������˵����ı���ȡ������Ч��
                }
            }
            if (place == 0)  //���place����Ϊ0����ʾû��������
            {
                MouseS = 0;  //��������ͣ״̬����
                flag = n + 1;  //���ñ�־����
            }
            else if (place == 2)  //���place����Ϊ2����ʾ����������
            {
                break;  //�˳�ѭ��
            }
        }
    }

}