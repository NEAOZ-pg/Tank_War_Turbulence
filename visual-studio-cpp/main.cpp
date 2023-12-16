#include <windows.h>
#include <time.h>
#include <iostream>
#include "global_param.h"
#include "map_create.h"
#include "key_interrupt.h"
#include "acllib.h"
#include "wall_map.h"
#include "tank.h"
#include "bullet.h"

#define BULLET_INTERVAL 8
#define TANK_DESTORY_INTERVAL 120

#define TIMEID_GAME 0

void timeevent(int timeID);

WallMap map_formal;
Tank tank1;
Tank tank2;
Bullet tank1_bullet0(1);
Bullet tank1_bullet1(1);
Bullet tank1_bullet2(1);
Bullet tank1_bullet3(1);
Bullet tank1_bullet4(1);
Bullet tank2_bullet0(2);
Bullet tank2_bullet1(2);
Bullet tank2_bullet2(2);
Bullet tank2_bullet3(2);
Bullet tank2_bullet4(2);
int tank1_bullet_interval;
int tank2_bullet_interval;
int tank_destory_interval;

char menu_start[] = "start.bmp";
char menu_pause[] = "pause.bmp";
char menu_intro[] = "introduction.bmp";
char menu_devel[] = "developer.bmp";
ACL_Image img_start;
ACL_Image img_pause;
ACL_Image img_intro;
ACL_Image img_devel;

int Setup()
{
	srand((unsigned int)time(NULL));
	//���ڴ�С��ʼ��
	initWindow("Test", 200, 50, WINDOW_LENGTH, WINDOW_WIDTH);
	//initConsole();
	//ͼƬ����
	loadImage(menu_start, &img_start);
	loadImage(menu_pause, &img_pause);
	loadImage(menu_intro, &img_intro);
	loadImage(menu_devel, &img_devel);
	//�ж�ʹ��
	registerMouseEvent(mouseevent);
	registerKeyboardEvent(keyevent);
	registerTimerEvent(timeevent);
	//��ʱ��ʹ��
	startTimer(TIMEID_GAME, 30);
	return 0;
}

void timeevent(int timeID)
{
	if (timeID == TIMEID_GAME)
	{	
		//menu�˵�
		if (interface_state == INTERFACE_MENU_BEGIN)
		{
			beginPaint();
			putImage(&img_start, 0, 0);
			endPaint();
			 
			if (Mouse_MENU_Start == 1)
			{
				interface_state = INTERFACE_GAME_INIT;
				Mouse_MENU_Start = 0;
			}
			else if (Mouse_MENU_INTRODUCTION == 1)
			{
				interface_state = INTERFACE_MENU_INTRODUCTION;
				Mouse_MENU_INTRODUCTION = 0;
			}
			else if (Mouse_MENU_DEVELPOMENT == 1)
			{
				interface_state = INTERFACE_MENU_DEVELPOER;
				Mouse_MENU_DEVELPOMENT = 0;
			}
			else if (Mouse_MENU_EXIT == 1)
			{
				ExitProcess(NULL);
			}
		}
		//INTRODUCTION�˵�
		else if (interface_state == INTERFACE_MENU_INTRODUCTION)
		{
			beginPaint();
			putImage(&img_intro, 0, 0);
			endPaint();

			if (Mouse_MENU_RETURN == 1)
			{
				interface_state = INTERFACE_MENU_BEGIN;
				Mouse_MENU_RETURN = 0;
			}
		}
		//DEVELPER�˵�
		else if (interface_state == INTERFACE_MENU_DEVELPOER)
		{
			beginPaint();
			putImage(&img_devel, 0, 0);
			endPaint();

			if (Mouse_MENU_RETURN == 1)
			{
				interface_state = INTERFACE_MENU_BEGIN;
				Mouse_MENU_RETURN = 0;
			}
		}
		//pause�˵�
		else if (interface_state == INTERFACE_MENU_PAUSE)
		{
			beginPaint();
			putImage(&img_pause, 0, 0);
			endPaint();

			if (Mouse_PAUSE_CONTINUE == 1)
			{
				beginPaint();
				//���ͼƬ
				WallMap::windows_clear();

				//map��tank��bullet��ʾ
				map_formal.wallmap_show();
				
				tank1.tank_show();
				tank2.tank_show();
				
				if (tank1_bullet0.is_exist()) tank1_bullet0.bullet_show();
				if (tank1_bullet1.is_exist()) tank1_bullet1.bullet_show();
				if (tank1_bullet2.is_exist()) tank1_bullet2.bullet_show();
				if (tank1_bullet3.is_exist()) tank1_bullet3.bullet_show();
				if (tank1_bullet4.is_exist()) tank1_bullet4.bullet_show();

				if (tank2_bullet0.is_exist()) tank2_bullet0.bullet_show();
				if (tank2_bullet1.is_exist()) tank2_bullet1.bullet_show();
				if (tank2_bullet2.is_exist()) tank2_bullet2.bullet_show();
				if (tank2_bullet3.is_exist()) tank2_bullet3.bullet_show();
				if (tank2_bullet4.is_exist()) tank2_bullet4.bullet_show();

				endPaint();

				//�û����̽���ʹ��
				Key_User1_ENABLE = 1;
				Key_User2_ENABLE = 1;

				//pause����ʾ
				interface_state = INTERFACE_GAME_PLAY;
				Mouse_PAUSE_CONTINUE = 0;
			}
			else if (Mouse_PAUSE_MENU == 1)
			{
				interface_state = INTERFACE_MENU_BEGIN;
				Mouse_PAUSE_MENU = 0;
			}
			else if (Mouse_PAUSE_EXIT == 1)
			{
				ExitProcess(NULL);
			}
		}
		//map��tank��bullet��ʼ��
		else if (interface_state == INTERFACE_GAME_INIT)
		{
			tank_destory_interval = -1;

			beginPaint();

			WallMap::windows_clear();

			//tank��ʼ��
			int length = 0, width = 0;
			int*** the_map = map_creating(&length, &width);
			WallMap map_init(length, width, the_map);
			map_formal = map_init;
			map_formal.wallmap_show();

			//�ӵ���ʼ����10��
			tank1_bullet0.clear();
			tank1_bullet1.clear();
			tank1_bullet2.clear();
			tank1_bullet3.clear();
			tank1_bullet4.clear();
			tank2_bullet0.clear();
			tank2_bullet1.clear();
			tank2_bullet2.clear();
			tank2_bullet3.clear();
			tank2_bullet4.clear();

			//tank1��ʼ��
			Tank tank_1(1, TANK1_COLOR, Tank::random_coordinate(map_formal), Tank::random_angle());
			tank1 = tank_1;
			tank1.tank_show();

			//tank2��ʼ��
			Tank tank_2(2, TANK2_COLOR, Tank::random_coordinate(map_formal), Tank::random_angle());
			tank2 = tank_2;
			tank2.tank_show();

			//�û����̽���ʹ��
			Key_User1_ENABLE = 1;
			Key_User2_ENABLE = 1;

			//pause����ʾ
			rectangle(1200, 700, WINDOW_LENGTH, WINDOW_WIDTH);

			endPaint();

			map_free(the_map, length, width);
			interface_state = INTERFACE_GAME_PLAY;
		}
		//��Ϸ
		else if (interface_state == INTERFACE_GAME_PLAY)
		{
			beginPaint();
			//tank1����������⣬��������Ӧ�Ĳ���
			if (key_A)
			{	
				tank1.tank_unshow();
				tank1.rotate_CCW_per_time();
				tank1.tank_show();
			}
			if (key_D)
			{
				tank1.tank_unshow();
				tank1.rotate_CW_per_time();
				tank1.tank_show();
			}
			if (key_W)
			{
				tank1.tank_unshow();
				tank1.move_for_per_time();
				tank1.tank_show();
			}
			if (key_S)
			{
				tank1.tank_unshow();
				tank1.move_back_per_time();
				tank1.tank_show();
			}
			//tank1�ӵ����
			if (key_SPACE && !tank1_bullet_interval)
			{
				POINT points[4];
				tank1.get_points(points);
				if (!tank1_bullet0.is_exist())
					tank1_bullet0.init(tank1.get_angle(), points);
				else if (!tank1_bullet1.is_exist())
					tank1_bullet1.init(tank1.get_angle(), points);
				else if (!tank1_bullet2.is_exist())
					tank1_bullet2.init(tank1.get_angle(), points);
				else if (!tank1_bullet3.is_exist())
					tank1_bullet3.init(tank1.get_angle(), points);
				else if (!tank1_bullet4.is_exist())
					tank1_bullet4.init(tank1.get_angle(), points);
				//��ֹ��ס����������bullet�ص����䣬���÷�����ʱ��
				tank1_bullet_interval = BULLET_INTERVAL;
			}
			//tank2����������⣬��������Ӧ�Ĳ���
			if (key_LEFT)
			{
				tank2.tank_unshow();
				tank2.rotate_CCW_per_time();
				tank2.tank_show();
			}
			if (key_RIGHT)
			{
				tank2.tank_unshow();
				tank2.rotate_CW_per_time();
				tank2.tank_show();
			}
			if (key_UP)
			{
				tank2.tank_unshow();
				tank2.move_for_per_time();
				tank2.tank_show();
			}
			if (key_DOWN)
			{
				tank2.tank_unshow();
				tank2.move_back_per_time();
				tank2.tank_show();
			}
			//tank2�ӵ����
			if (key_ENTER && !tank2_bullet_interval)
			{
				POINT points[4];
				tank2.get_points(points);
				if (!tank2_bullet0.is_exist())
					tank2_bullet0.init(tank2.get_angle(), points);
				else if (!tank2_bullet1.is_exist())
					tank2_bullet1.init(tank2.get_angle(), points);
				else if (!tank2_bullet2.is_exist())
					tank2_bullet2.init(tank2.get_angle(), points);
				else if (!tank2_bullet3.is_exist())
					tank2_bullet3.init(tank2.get_angle(), points);
				else if (!tank2_bullet4.is_exist())
					tank2_bullet4.init(tank2.get_angle(), points);
				//��ֹ��ס����������bullet�ص����䣬���÷�����ʱ��
				tank2_bullet_interval = BULLET_INTERVAL;
			}

			//�ж�bullet�Ƿ�ײ��tank�����ƶ�bullet
			int destory[10];
			memset(destory, 0, sizeof(destory));
			
			if (tank1_bullet0.is_exist())	destory[0] = tank1_bullet0.pre_time();
			if (tank1_bullet1.is_exist())	destory[1] = tank1_bullet1.pre_time();
			if (tank1_bullet2.is_exist())	destory[2] = tank1_bullet2.pre_time();
			if (tank1_bullet3.is_exist())	destory[3] = tank1_bullet3.pre_time();
			if (tank1_bullet4.is_exist())	destory[4] = tank1_bullet4.pre_time();

			if (tank2_bullet0.is_exist())	destory[5] = tank2_bullet0.pre_time();
			if (tank2_bullet1.is_exist())	destory[6] = tank2_bullet1.pre_time();
			if (tank2_bullet2.is_exist())	destory[7] = tank2_bullet2.pre_time();
			if (tank2_bullet3.is_exist())	destory[8] = tank2_bullet3.pre_time();
			if (tank2_bullet4.is_exist())	destory[9] = tank2_bullet4.pre_time();

			int i = 0;
			for (i = 0; i < 10; ++i)
			{
				if (destory[i] == -1)
				{
					tank1.tank_unshow();
					Key_User1_ENABLE = 0;
					user1_key_remake();
					if (tank_destory_interval == -1)
						tank_destory_interval = TANK_DESTORY_INTERVAL;
				}
				else if (destory[i] == -2)
				{
					tank2.tank_unshow();
					Key_User2_ENABLE = 0;
					user2_key_remake();
					if (tank_destory_interval == -1)
						tank_destory_interval = TANK_DESTORY_INTERVAL;
				}

			}
			map_formal.wallmap_show();

			endPaint();
			
			//tank1&tank2���ӵ��������Լ�
			if (tank1_bullet_interval)	--tank1_bullet_interval;
			if (tank2_bullet_interval)	--tank2_bullet_interval;

			//һ����������Ϸ����ʱ
			if (tank_destory_interval > 0)	--tank_destory_interval;
			else if (tank_destory_interval == 0) interface_state = INTERFACE_GAME_INIT;

			//��ͣ�����
			if (Mouse_PLAY_PAUSE == 1)
			{
				//���ü���
				Key_User1_ENABLE = 0;
				Key_User2_ENABLE = 0;
				interface_state = INTERFACE_MENU_PAUSE;
				Mouse_PLAY_PAUSE = 0;
			}
		}
	}
}