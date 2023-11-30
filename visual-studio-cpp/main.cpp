#include "acllib.h"
#include "wall_map.h"

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

int Setup()
{
	initWindow("Test", 200, 50, 1300, 800);

	beginPaint();

	//修改map_init & testmap的前两个参数与map1 | 2 的长宽对应
	map_init(4,3);

	WallMap testmap(4, 3, testmap);

	testmap.wallmap_show();

	endPaint();

	return 0;
}