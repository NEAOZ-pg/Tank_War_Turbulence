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

void keyevent(int key, int event);

#endif