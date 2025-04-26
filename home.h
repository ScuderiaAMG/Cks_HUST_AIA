#ifndef _HOME_H_
#define _HOME_H_

#define MAX_ITEMS 20
#define BTN_WIDTH 250
#define BTN_HEIGHT 40
#define MAX_FILES 20  // �����ļ���������

// ״̬ö��
enum { SELECT_USER, SELECT_CATEGORY, SELECT_FILE, SHOW_CONTENT };
int home_page(INFO *temp, int language);
void home_button_recovery(int num, int language);
void home_button_light(int flag, int language);

void home_screen(int language);



#endif