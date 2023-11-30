#include <windows.h>
#include <time.h>
#include "acllib.h"
#include "wall_map.h"
#include "tank.h"

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
����µĵ�ͼ

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
				//����map2Ϊmap1���ɻ��map1�ĵ�ͼ
			}
		}
	}
}

int Setup()
{
	initWindow("Test", 200, 50, 1300, 800);
	srand((unsigned int)time(0));
	//initConsole();

	beginPaint();

	//�޸�map_init & testmap��ǰ����������map1 | 2 �ĳ����Ӧ
	map_init(4,3);
	WallMap testmap(4, 3, testmap);
	testmap.wallmap_show();

	Tank tank0(0, random_coordinate(testmap), 0, 15, 10, 3);
	tank0.tank_show(testmap,GREEN);

	Tank tank1(1, random_coordinate(testmap), 0, 15, 10, 3);
	tank1.tank_show(testmap, BLUE);

	endPaint();

	return 0;
}