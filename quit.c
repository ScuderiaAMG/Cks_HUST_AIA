#include "quit.h"
#include "public.h"
#include "main.h"

void quit_page(void)
{
    int i=0,time=0,color=2;
    char string[8][10]={"T","TH","THA","THAN","THANK","THANKY","THANKYO","THANKYOU"};
    char (*pstr)[10] = string;
    cleardevice();
    setbkcolor(WHITE);
    do{
        setcolor(color);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
        outtextxy(80,160,pstr[i]);
        i++;
        time++;
        color++;
        if(color>15)
        {
            color = 2;
        }
        if(i>8) 
        {
            i=0;
            cleardevice();
            continue;
        }
        delay(500);
    }while(time<8);
    closegraph();
}