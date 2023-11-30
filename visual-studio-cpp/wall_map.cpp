#include "wall_map.h"
#include "acllib.h"
#include <stdlib.h>

//�����������뵽ʱ����Ҫ��70�ĳɱ����������ͼ�����Ĺ�������
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
	//������Ҫ�����ӵ��㷨��map����
	_axis_x = 100;
	_axis_y = 100;	

	//����malloc�ĳ�new
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

WallMap::~WallMap()	//��һ������
{
	free(wallmap);
}

/**
  * @brief  �ж�SolidObject�Ƿ�crash Map
  * @param  line�������꣨��Ӧwidth��
  * @param	column: �����꣨��Ӧlength��	
  * @retval frontier[4]: f[0]��up��f[1]��down��f[2]��left��f[3]��right
						1 ���ϰ�		0 ���ϰ�
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
  * @brief  ����Map
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
