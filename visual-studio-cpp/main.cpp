#include <windows.h>
#include <time.h>
#include <iostream>
#include "acllib.h"
#include "wall_map.h"
#include "tank.h"

#define interface_game_init 0
#define interface_game_play 1

#define TimeID_Game 0

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

void keyevent(int key, int event);
void timeevent(int timeID);
int key_A = 0;
int key_W = 0;
int key_S = 0;
int key_D = 0;

int interface_state = 0;

int center_init[2] = { 50,50 };
Tank tank0(1, BLUE, center_init, 30, 25, 15, 3);
WallMap map_test;

int Setup()		//
{
	srand((unsigned int)time(0));
	initWindow("Test", 200, 50, 1300, 800);
	initConsole();
	registerKeyboardEvent(keyevent);
	registerTimerEvent(timeevent);
	startTimer(0, 20);
	beginPaint();


	/*Tank tank1(1, BLUE, random_coordinate(testmap), 30, 25, 15, 3);
	tank1.tank_show();
	tank1.tank_unshow();*/

	endPaint();

		//if (key_A)
		//{
		//	std::cout << "A\n";
		//	key_A = 0;
		//}


	return 0;
}

int main()
{
	while (1) {
		std::cout << "OK!\n";
	}
}

void keyevent(int key, int event)
{
	if (event == KEY_DOWN)
	{
		if (key == 0x41)
		{
			std::cout << "A = 1\n";
			key_A = 1;
		}
		else if (key == 0x57)
		{
			std::cout << "W = 1\n";
			key_W = 1;
		}
		else if (key == 0x53)
		{
			std::cout << "S = 1\n";
			key_S = 1;
		}
		else if (key == 0x44)
		{
			std::cout << "D = 1\n";
			key_D = 1;
		}
	}
	else if (event == KEY_UP)
	{
		if (key == 0x41)
		{
			std::cout << "A = 0\n";
			key_A = 0;
		}
		else if (key == 0x57)
		{
			std::cout << "W = 0\n";
			key_W = 0;
		}
		else if (key == 0x53)
		{
			std::cout << "S = 0\n";
			key_S = 0;
		}
		else if (key == 0x44)
		{
			std::cout << "D = 0\n";
			key_D = 0;
		}
	}
}

void timeevent(int timeID)
{
	if (timeID == TimeID_Game)
	{
		if (interface_state == interface_game_init)
		{
			beginPaint();

			map_init(4, 3);
			WallMap map_i(4, 3, testmap);
			map_test = map_i;
			map_test.wallmap_show();

			Tank tank(0, GREEN, random_coordinate(map_test), 50, 25, 15, 3);
			tank0 = tank;
			tank0.tank_show();

			endPaint();

			interface_state = 1;
		}
		else if (interface_state == interface_game_play)
		{
			if (key_A)
			{
				beginPaint();
				
				tank0.tank_unshow();
				tank0.rotate_CCW_per_time();
				tank0.tank_show();

				endPaint();
			}
			if (key_D)
			{
				beginPaint();

				tank0.tank_unshow();
				tank0.rotate_CW_per_time();
				tank0.tank_show();

				endPaint();
			}
		}
	}
}
