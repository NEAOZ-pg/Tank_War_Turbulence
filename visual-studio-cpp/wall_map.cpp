#include <Windows.h>
#include "wall_map.h"

#include <iostream>
#include <cstring>
#include "acllib.h"

WallMap::WallMap(int length, int width, int*** map) :
	_length(length), _width(width)
{
	//后期需要更复杂的算法让map居中
	_axis_x = 100;
	_axis_y = 100;

	wallmap = new int** [_width];
	int line = 0, column = 0, i = 0;
	for (line = 0; line < _width; line++)
	{
		wallmap[line] = new int* [_length];
		for (column = 0; column < _length; column++)
		{
			wallmap[line][column] = new int[4];
			for (i = 0; i < 4; i++)
			{
				wallmap[line][column][i] = map[line][column][i];
			}
		}
	}

}

WallMap::WallMap(const WallMap& w)
{
	_length = w._length;
	_width = w._width;
	_axis_x = w._axis_x;
	_axis_y = w._axis_y;

	wallmap = new int** [_width];
	int line = 0, column = 0, i = 0;
	for (line = 0; line < _width; line++)
	{
		wallmap[line] = new int* [_length];
		for (column = 0; column < _length; column++)
		{
			wallmap[line][column] = new int[4];
			for (i = 0; i < 4; i++)
			{
				wallmap[line][column][i] = w.wallmap[line][column][i];
			}
		}
	}

}

WallMap::~WallMap()
{
	int i = 0, j = 0;
	for (i = 0; i < _width; i++)
	{
		for (j = 0; j < _length; j++)
		{
			delete[] wallmap[i][j];
		}
		delete[] wallmap[i];
	}
	delete[] wallmap;
	wallmap = NULL;
}

//private
/**
  * @brief  判断SolidObject是否crash Map
  * @param  line：行坐标（对应width）
  * @param	column: 列坐标（对应length）
  * @retval frontier[4]: f[0]：up，f[1]：down，f[2]：left，f[3]：right
						1 有障碍		0 无障碍
  */
int* WallMap::_get_frontier(int line, int column)
{
	int frontier[4] = { 0,0,0,0, };
	int i = 0;
	for (i = 0; i < 4; i++)
		frontier[i] = wallmap[line][column][i];

	return frontier;
}

void WallMap::_wallmap_showoneblank(int line, int column)
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
			rectangle(_axis_x + UNIT_LENGTH * column - UNIT_LINE, 
				_axis_y + UNIT_LENGTH * line + i % 2 * (UNIT_LENGTH - UNIT_LINE),
				_axis_x + UNIT_LENGTH * column + (UNIT_LENGTH + UNIT_LINE),
				_axis_y + UNIT_LENGTH * line + i % 2 * (UNIT_LENGTH - UNIT_LINE) + UNIT_LINE);
	}

	for (i = 2; i < 4; i++)
	{
		if (wallmap[line][column][i])
			rectangle(_axis_x + UNIT_LENGTH * column + i % 2 * (UNIT_LENGTH - UNIT_LINE),
				_axis_y + UNIT_LENGTH * line - UNIT_LINE,
				_axis_x + UNIT_LENGTH * column + i % 2 * (UNIT_LENGTH - UNIT_LINE) + UNIT_LINE,
				_axis_y + UNIT_LENGTH * line + (UNIT_LENGTH + UNIT_LINE));
	}
}

void WallMap::_wallmap_showframe()
{
	setBrushColor(BLACK);
	setBrushStyle(BRUSH_STYLE_SOLID);

	setPenColor(BLACK);
	setPenWidth(0);
	setPenStyle(PEN_STYLE_SOLID);

	rectangle(_axis_x - UNIT_LINE, _axis_y - UNIT_LINE,
		_axis_x + UNIT_LENGTH * _length + UNIT_LINE, _axis_y);
	rectangle(_axis_x - UNIT_LINE, _axis_y - UNIT_LINE,
		_axis_x, _axis_y + UNIT_LENGTH * _width + UNIT_LINE);
	rectangle(_axis_x + UNIT_LENGTH * _length, _axis_y - UNIT_LINE,
		_axis_x + UNIT_LENGTH * _length + UNIT_LINE, _axis_y + UNIT_LENGTH * _width + UNIT_LINE);
	rectangle(_axis_x - UNIT_LINE, _axis_y + UNIT_LENGTH * _width,
		_axis_x + UNIT_LENGTH * _length + UNIT_LINE, _axis_y + UNIT_LENGTH * _width + UNIT_LINE);
}


//public
int WallMap::get_axis_x()
{
	return _axis_x;
}

int WallMap::get_axis_y()
{
	return _axis_y;
}

int WallMap::get_length()
{
	return _length;
}

int WallMap::get_width()
{
	return _width;
}

/**
  * @brief  计算出在相邻九宫格的相对坐标（左上角为原点）
  * @param  center[2] ： Wall_Map坐标系的坐标
  * @retval new_center[2] : 在相邻九宫格的相对坐标
  */
int* WallMap::get_rela_quare_nine_center(int* center)
{
	int new_center[2];

	new_center[0] = center[0] % UNIT_LENGTH;
	new_center[1] = center[1] % UNIT_LENGTH;

	return new_center;
}

/**
  * @brief  计算相邻九宫格的墙壁具体情况
  * @param  center[2] ： 总坐标系的坐标
  * @retval nine_map[3 * UNIT_LENGTH][3 * UNIT_LENGTH] 
  *					1 : 有障碍		0 ：无障碍
  */
int** WallMap::get_square_nine(int* center)
{
	const int move[3][3][2] = 
	{
		{ {-1,-1}, {-1,0}, {-1,1},},
		{ {0,-1}, {0,0}, {0,1},},
		{ {1,-1}, {1,0}, {1,1},},
	};
	int new_center[2] = { center[0] / UNIT_LENGTH,center[1] / UNIT_LENGTH };
	
	int **nine_map;
	int i = 0, j = 0;

	nine_map = (int**)malloc(sizeof(int*) * UNIT_LENGTH);
	for (i = 0; i < 3 * UNIT_LENGTH; i++)
	{
		nine_map[i] = (int*)malloc(sizeof(int) * UNIT_LENGTH);
		for (j = 0; j < 3 * UNIT_LENGTH; j++)
			nine_map[i][j] = 0;
	}
	
	for(i = 0;i < 3;i++)
		for (j = 0; j < 3; j++)
		{
			//i 为 line，j 为 column，
			//先给 y（line）,再给 x （column） 按照行读取
			int* frontier = _get_frontier(center[1] + move[i][j][1], center[0] + move[i][j][0]);
			int x = j * UNIT_LENGTH, y = i * UNIT_LENGTH;
			int m = 0, n = 0;
			if (frontier[0])
			{
				for (m = x; m < x + UNIT_LENGTH; m++)
					for (n = y; n < y + UNIT_LINE; n++)
						nine_map[m][n] = 1;
			}
			if (frontier[1])
			{
				for (m = x; m < x + UNIT_LENGTH; m++)
					for (n = y + UNIT_LENGTH - UNIT_LINE; n < y + UNIT_LENGTH; n++)
						nine_map[m][n] = 1;
			}
			if (frontier[2])
			{
				for (m = x; m < x + UNIT_LINE; m++)
					for (n = y; n < y + UNIT_LENGTH; n++)
						nine_map[m][n] = 1;
			}
			if (frontier[3])
			{
				for (m = x + UNIT_LENGTH - UNIT_LINE; m < x + UNIT_LENGTH; m++)
					for (n = y; n < y + UNIT_LENGTH; n++)
						nine_map[m][n] = 1;
			}
		}

	return nine_map;
}

void WallMap::free_square_nine(int** nine_map)
{
	int i = 0, j = 0;
	for (i = 0; i < 3 * UNIT_LENGTH; i++)
	{
		free(nine_map[i]);
	}
	free(nine_map);
	nine_map = NULL;
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
			_wallmap_showoneblank(line, column);
	
	_wallmap_showframe();
}
