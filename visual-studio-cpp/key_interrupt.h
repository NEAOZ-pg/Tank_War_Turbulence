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

extern int Mouse_LEFT_Start;
extern int Mouse_LEFT_Continue;
extern int Mouse_LEFT_Restart;
extern int Mouse_LEFT_EXIT;
extern int Mouse_LEFT_Pause;

void keyevent(int key, int event);
void mouseevent(int x, int y, int button, int event);

#endif
