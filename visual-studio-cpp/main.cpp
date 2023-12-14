#include <windows.h>
#include <time.h>
#include <iostream>
#include "map_create.h"
#include "key_interrupt.h"
#include "acllib.h"
#include "wall_map.h"
#include "tank.h"
#include "bullet.h"

#define INTERFACE_GAME_INIT 0
#define INTERFACE_GAME_PLAY 1
#define BULLET_INTERVAL 10
#define TANK_DESTORY_INTERVAL 150

#define TIMEID_GAME 0

void timeevent(int timeID);

int interface_state = 0;

WallMap map_test;
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

int Setup()		//	
{
	//menu��
	/*
	���Լ�д��menu����ɺ������ڸô����У���ʾmenu
	����ÿ�����涼��	��һ������������ָ������setup���������һ����������������������Ҳ��ܣ�	�Ϳ�����windows����ʾ
	���ڽ������ת����ʱͨ��	�ֶ����������һ��������Ȼ���ٴα�������		��ʵ�ֲ�ͬ�˵��ġ���Ӳ�л�����
	�Ȱ������������ʣ�����˵
	*/
	srand(time(NULL));
	initWindow("Test", 200, 50, WINDOW_LENGTH, WINDOW_WIDTH);
	initConsole();
	registerKeyboardEvent(keyevent);
	registerTimerEvent(timeevent);
	startTimer(0, 20);
	return 0;
}

void timeevent(int timeID)
{
	if (timeID == TIMEID_GAME)
	{
		if (interface_state == INTERFACE_GAME_INIT)
		{
			tank_destory_interval = -1;

			beginPaint();
			
			windows_clear();

			int length = 0, width = 0;
			testmap = map_creating(&length, &width);
			WallMap map_init(length, width, testmap);
			map_test = map_init;
			map_test.wallmap_show();
			map_free(testmap, length, width);
			Tank tank_1(1, TANK1_COLOR, random_coordinate(map_test), random_angle());
			tank1 = tank_1;
			tank1.tank_show();

			Tank tank_2(2, TANK2_COLOR, random_coordinate(map_test), random_angle());
			tank2 = tank_2;
			tank2.tank_show();

			endPaint();

			interface_state = INTERFACE_GAME_PLAY;
		}
		else if (interface_state == INTERFACE_GAME_PLAY)
		{
			if (key_A)
			{
				beginPaint();
				
				tank1.tank_unshow();
				tank1.rotate_CCW_per_time();
				tank1.tank_show();

				endPaint();
			}
			if (key_D)
			{
				beginPaint();

				tank1.tank_unshow();
				tank1.rotate_CW_per_time();
				tank1.tank_show();

				endPaint();
			}
			if (key_W)
			{
				beginPaint();

				tank1.tank_unshow();
				tank1.move_for_per_time();
				tank1.tank_show();

				endPaint();
			}
			if (key_S)
			{
				beginPaint();

				tank1.tank_unshow();
				tank1.move_back_per_time();
				tank1.tank_show();

				endPaint();
			}
			if (key_SPACE && !tank1_bullet_interval)
			{
				POINT* points = tank1.get_points();
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
				delete[] points;

				tank1_bullet_interval = BULLET_INTERVAL;
			}
			if (key_LEFT)
			{
				beginPaint();

				tank2.tank_unshow();
				tank2.rotate_CCW_per_time();
				tank2.tank_show();

				endPaint();
			}
			if (key_RIGHT)
			{
				beginPaint();

				tank2.tank_unshow();
				tank2.rotate_CW_per_time();
				tank2.tank_show();

				endPaint();
			}
			if (key_UP)
			{
				beginPaint();

				tank2.tank_unshow();
				tank2.move_for_per_time();
				tank2.tank_show();

				endPaint();
			}
			if (key_DOWN)
			{
				beginPaint();

				tank2.tank_unshow();
				tank2.move_back_per_time();
				tank2.tank_show();

				endPaint();
			}
			if (key_ENTER && !tank2_bullet_interval)
			{
				POINT* points = tank2.get_points();
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
				delete[] points;

				tank2_bullet_interval = BULLET_INTERVAL;
			}

			int destory[10];
			memset(destory, 0, sizeof(destory));

			beginPaint();
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
					key_A = 0;
					key_D = 0;
					key_W = 0;
					key_S = 0;
					key_SPACE = 0;
					if (tank_destory_interval == -1)
						tank_destory_interval = TANK_DESTORY_INTERVAL;
				}
				else if (destory[i] == -2)
				{
					tank2.tank_unshow();
					Key_User2_ENABLE = 0;
					key_LEFT = 0;
					key_RIGHT = 0;
					key_UP = 0;
					key_DOWN = 0;
					key_ENTER = 0;
					if (tank_destory_interval == -1)
						tank_destory_interval = TANK_DESTORY_INTERVAL;
				}

			}
			map_test.wallmap_show();

			tank1_bullet0.anti_bug();
			tank1_bullet1.anti_bug();
			tank1_bullet2.anti_bug();
			tank1_bullet3.anti_bug();
			tank1_bullet4.anti_bug();

			tank2_bullet0.anti_bug();
			tank2_bullet1.anti_bug();
			tank2_bullet2.anti_bug();
			tank2_bullet3.anti_bug();
			tank2_bullet4.anti_bug();

			map_test.wallmap_show();

			if (tank1_bullet_interval)	--tank1_bullet_interval;
			if (tank2_bullet_interval)	--tank2_bullet_interval;
			if (tank_destory_interval > 0)	--tank_destory_interval;
			else if (tank_destory_interval == 0)
			{
				Key_User1_ENABLE = 1;
				Key_User1_ENABLE = 1;
				interface_state = INTERFACE_GAME_INIT;
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
			}

			endPaint();
		}
	}
}
