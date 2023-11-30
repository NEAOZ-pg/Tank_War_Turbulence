#include "wall_map.h"
#include "acllib.h"
#include <stdlib.h>

//以下两个代码到时候需要将70改成变量以满足地图放缩的功能需求
void WallMap::wallmap_showoneblank(int line, int column)
{
	setBrushColor(BLACK);
	setBrushStyle(BRUSH_STYLE_SOLID);

	setPenColor(BLACK);
	setPenWidth(0);
	setPenStyle(PEN_STYLE_SOLID);

	int i = 0;
	for (i = 0; i < 2; i++)
	{
		if(wallmap[line][column][i])
			rectangle(_axis_x + 70 * column - 5, _axis_y + 70 * line + i % 2 * 65,
				_axis_x + 70 * column + 75, _axis_y + 70 * line + i % 2 * 65 + 5);
	}

	for (i = 2; i < 4; i++)
	{
		if (wallmap[line][column][i])
			rectangle(_axis_x + 70 * column + i % 2 * 65, _axis_y + 70 * line - 5,
				_axis_x + 70 * column + i % 2 * 65 + 5, _axis_y + 70 * line + 75);
	}
}

void WallMap::wallmap_showframe()
{
	setBrushColor(BLACK);
	setBrushStyle(BRUSH_STYLE_SOLID);

	setPenColor(BLACK);
	setPenWidth(0);
	setPenStyle(PEN_STYLE_SOLID);

	rectangle(_axis_x - 5, _axis_y - 5,
		_axis_x + 70 * _length + 5, _axis_y);
	rectangle(_axis_x - 5, _axis_y - 5,
		_axis_x, _axis_y + 70 * _width + 5);
	rectangle(_axis_x + 70 * _length, _axis_y - 5,
		_axis_x + 70 * _length + 5, _axis_y + 70 * _width + 5);
	rectangle(_axis_x - 5, _axis_y + 70 * _width,
		_axis_x + 70 * _length + 5, _axis_y + 70 * _width + 5);
}

WallMap::WallMap(int length, int width,int*** map):
	_length(length),_width(width)
{
	//后期需要更复杂的算法让map居中
	_axis_x = 100;
	_axis_y = 100;	

	//建议malloc改成new
	wallmap = (int***)malloc(sizeof(int**) * width);
	int line = 0, column = 0, i = 0;
	for (line = 0; line < width; line++)
	{
		wallmap[line] = (int**)malloc(sizeof(int*) * length);
		for (column = 0; column < length; column++)
		{
			wallmap[line][column] = (int*)malloc(sizeof(int) * 4);
			for (i = 0; i < 4; i++)
			{
				wallmap[line][column][i] = map[line][column][i];
			}
		}
	}
		
}

WallMap::~WallMap()	//有一点问题
{
	free(wallmap);
}

/**
  * @brief  判断SolidObject是否crash Map
  * @param  line：行坐标（对应width）
  * @param	column: 列坐标（对应length）	
  * @retval frontier[4]: f[0]：up，f[1]：down，f[2]：left，f[3]：right
						1 有障碍		0 无障碍
  */
int* WallMap::get_frontier(int line, int column)
{
	int frontier[4] = { 0,0,0,0, };
	int i = 0;
	for (i = 0; i < 4; i++)
		frontier[i] = wallmap[line][column][i];

	return frontier;
}
/**
  * @brief  绘制Map
  * @param  None
  * @retval None
  */
void WallMap::wallmap_show()
{
	int line = 0, column = 0;
	for (line = 0; line < _width; line++)
		for (column = 0; column < _length; column++)
			wallmap_showoneblank(line, column);
	
	wallmap_showframe();
}
