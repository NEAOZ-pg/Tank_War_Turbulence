#ifndef __GLOBAL_PARAM_H__
#define __GLOBAL_PARAM_H__

#include "acllib.h"
//一些main.cpp需要与其他文件共享的全局变量

#define INTERFACE_GAME_INIT			0
#define INTERFACE_GAME_PLAY			1
#define INTERFACE_MENU_BEGIN		2
#define INTERFACE_MENU_PAUSE		3
#define INTERFACE_MENU_INTRODUCTION 4
#define INTERFACE_MENU_DEVELPOER	5

extern int interface_state;

extern char menu_start[];
extern char menu_pause[];
extern char menu_intro[];
extern char menu_devel[];
extern char bott_pause[];
extern char tank_blue[];
extern char tank_green[];
extern char font_name[];

extern ACL_Image img_start;
extern ACL_Image img_pause;
extern ACL_Image img_intro;
extern ACL_Image img_devel;
extern ACL_Image img_botto;
extern ACL_Image img_Tankblue;
extern ACL_Image img_Tankgreen;

#endif
