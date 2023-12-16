#include "wall_map.h"
#include "stdlib.h"

//INIT

WallMap::WallMap()
{
	_axis_x = 0;
	_axis_y = 0;
	_length = 0;
	_width = 0;
	wallmap = NULL;
}

WallMap::WallMap(int length, int width, int*** map) :
	_length(length), _width(width)
{
	_axis_x = (WINDOW_LENGTH - _length * UNIT_LENGTH) / 2;
	_axis_y = 50;//������Ҫ�ı�

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

WallMap& WallMap::operator=(const WallMap& map1)
{
	this->_length = map1._length;
	this->_width = map1._width;
	this->_axis_x = map1._axis_x;
	this->_axis_y = map1._axis_y;

	this->wallmap = new int** [_width];
	int line = 0, column = 0, i = 0;
	for (line = 0; line < _width; line++)
	{
		this->wallmap[line] = new int* [_length];
		for (column = 0; column < _length; column++)
		{
			this->wallmap[line][column] = new int[4];
			for (i = 0; i < 4; i++)
			{
				this->wallmap[line][column][i] = map1.wallmap[line][column][i];
			}
		}
	}
	return *this;
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
  * @brief  ����һ����λblock���ıߵ�Wallmap
  * @param  line��0��ʼ
  * @param	column: 0��ʼ
  * @retval None
  */
void WallMap::_wallmap_showoneblock(int line, int column)
{
	setBrushColor(BLACK);
	setBrushStyle(BRUSH_STYLE_SOLID);

	setPenColor(BLACK);
	setPenWidth(1);
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

/**
  * @brief  �Ӵ�Map�ı߿򣬷�ֹMap�߿򴩽ǣ�����ɾ�������������BUG��
  * @param  None
  * @retval None
  */
void WallMap::_wallmap_showframe()
{
	setBrushColor(BLACK);
	setBrushStyle(BRUSH_STYLE_SOLID);

	setPenColor(BLACK);
	setPenWidth(1);
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
			_wallmap_showoneblock(line, column);
	
	_wallmap_showframe();
}

/**
  * @brief  ��մ�����Ļ
  * @param  None
  * @retval None
  */
void WallMap::windows_clear()
{
	setBrushColor(WHITE);
	setBrushStyle(BRUSH_STYLE_SOLID);

	setPenColor(WHITE);
	setPenWidth(0);
	setPenStyle(PEN_STYLE_SOLID);

	rectangle(0, 0, WINDOW_LENGTH, WINDOW_WIDTH);
}
