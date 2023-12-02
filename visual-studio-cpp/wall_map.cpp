#include <Windows.h>
#include "wall_map.h"

#include <iostream>
#include <cstring>
#include "acllib.h"

WallMap::WallMap(int length, int width, int*** map) :
	_length(length), _width(width)
{
	//������Ҫ�����ӵ��㷨��map����
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
  * @brief  �ж�SolidObject�Ƿ�crash Map
  * @param  line�������꣨��Ӧwidth��
  * @param	column: �����꣨��Ӧlength��
  * @retval frontier[4]: f[0]��up��f[1]��down��f[2]��left��f[3]��right
						1 ���ϰ�		0 ���ϰ�
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
  * @brief  ����Map
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
