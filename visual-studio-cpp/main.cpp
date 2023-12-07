#include <windows.h>
#include <time.h>
#include <iostream>
#include "global_param.h"
#include "key_interrupt.h"
#include "acllib.h"
#include "wall_map.h"
#include "tank.h"
#include "bullet.h"

#define INTERFACE_GAME_INIT 0
#define INTERFACE_GAME_PLAY 1
#define BULLET_INTERVAL 10

#define TIMEID_GAME 0

//UP DOWN LEFT RIGHT
int map1[3][3][4] = {
	{{1,1,1,0},{1,0,0,1},{1,0,1,1},},
	{{1,0,1,1},{0,1,1,0},{0,0,0,1},},
	{{0,1,1,0},{1,1,0,0},{0,1,0,1},},
};

int map2[3][4][4] = {
	{{1,1,1,0},{1,0,0,1},{1,0,1,0},{1,1,0,1},},
	{{1,0,1,1},{0,1,1,0},{0,0,0,1},{1,0,1,1},},
	{{0,1,1,0},{1,1,0,0},{0,1,0,0},{0,1,0,1},},
};

/*
添加新的地图

*/

int*** testmap;
void map_init(int length,int width)
{
	testmap = (int***)malloc(sizeof(int**) * width);
	int line = 0, column = 0, i = 0;
	for (line = 0; line < width; line++)
	{
		testmap[line] = (int**)malloc(sizeof(int*) * length);
		for (column = 0; column < length; column++)
		{
			testmap[line][column] = (int*)malloc(sizeof(int) * 4);
			for (i = 0; i < 4; i++)
			{
				testmap[line][column][i] = map2[line][column][i];
				//更改map2为map1即可获得map1的地图
			}
		}
	}
}

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

int Setup()		//	
{
	//menu：
	/*
	将自己写的menu打包成函数，在该处运行，显示menu
	满足每个界面都用	仅一个函数（这里指仅能在setup里面仅调用一个函数，函数里面的事情我不管）	就可以在windows上显示
	至于界面的跳转，暂时通过	手动更改上面的一个函数，然后再次编译运行		来实现不同菜单的“”硬切换“”
	先把这个做出来，剩余的再说
	*/
	srand((unsigned int)time(0));
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
			beginPaint();

			map_init(4, 3);
			WallMap map_i(4, 3, testmap);
			map_test = map_i;
			map_test.wallmap_show();
			Tank tank_1(1, GREEN, random_coordinate(map_test), random_angle());
			tank1 = tank_1;
			tank1.tank_show();

			Tank tank_2(2, BLUE, random_coordinate(map_test), random_angle());
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
		}

		beginPaint();
		if (tank1_bullet0.is_exist())	tank1_bullet0.pre_time();
		if (tank1_bullet1.is_exist())	tank1_bullet1.pre_time();
		if (tank1_bullet2.is_exist())	tank1_bullet2.pre_time();
		if (tank1_bullet3.is_exist())	tank1_bullet3.pre_time();
		if (tank1_bullet4.is_exist())	tank1_bullet4.pre_time();

		if (tank2_bullet0.is_exist())	tank2_bullet0.pre_time();
		if (tank2_bullet1.is_exist())	tank2_bullet1.pre_time();
		if (tank2_bullet2.is_exist())	tank2_bullet2.pre_time();
		if (tank2_bullet3.is_exist())	tank2_bullet3.pre_time();
		if (tank2_bullet4.is_exist())	tank2_bullet4.pre_time();
		endPaint();

		if (tank1_bullet_interval)	--tank1_bullet_interval;
		if (tank2_bullet_interval)	--tank2_bullet_interval;
	}
}
