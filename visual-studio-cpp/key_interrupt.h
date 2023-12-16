#ifndef __KEY_INTERRUPT_H__
#define __KEY_INTERRUPT_H__

extern int key_A;
extern int key_W;
extern int key_S;
extern int key_D;
extern int key_UP;
extern int key_DOWN;
extern int key_LEFT;
extern int key_RIGHT;
extern int key_ENTER;
extern int key_SPACE;

extern int Key_User1_ENABLE;
extern int Key_User2_ENABLE;

extern int Mouse_MENU_Start;
extern int Mouse_MENU_INTRODUCTION;
extern int Mouse_MENU_DEVELPOMENT;
extern int Mouse_MENU_EXIT;
extern int Mouse_PAUSE_CONTINUE;
extern int Mouse_PAUSE_MENU;
extern int Mouse_PAUSE_EXIT;
extern int Mouse_PLAY_PAUSE;
extern int Mouse_MENU_RETURN;

void user1_key_remake();
void user2_key_remake();
void keyevent(int key, int event);
void mouseevent(int x, int y, int button, int event);

#endif
