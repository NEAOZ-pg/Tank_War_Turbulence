#ifndef __GLOBAL_PARAM_H__
#define __GLOBAL_PARAM_H__

//一些main.cpp需要与其他文件共享的全局变量

#define INTERFACE_GAME_INIT			0
#define INTERFACE_GAME_PLAY			1
#define INTERFACE_MENU_BEGIN		2
#define INTERFACE_MENU_PAUSE		3
#define INTERFACE_MENU_INTRODUCTION 4
#define INTERFACE_MENU_DEVELPOER	5

extern int interface_state;

#endif
