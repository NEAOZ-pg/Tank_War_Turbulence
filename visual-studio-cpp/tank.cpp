#include <Windows.h>
#include <stdlib.h>

#include "tank.h"

#include "acllib.h"
#include "wall_map.h"

Tank::Tank(int user, int* center, int angle, int half_length, int half_width, int speed) :
	SolidObject(user, center, angle, half_length, half_width, speed)
{
}

Tank::~Tank()
{
}

//private
POINT* Tank::_get_point(WallMap my_map)
{
	POINT point[4];

	int i = 0;
	int move[4][2] =
	{
		{_half_length , _half_width},
		{_half_length , -_half_width},
		{-_half_length ,-_half_width},
		{-_half_length , _half_width},
	};

	for (i = 0; i < 4; i++)
	{
		point[i].x = _center[0] + move[i][0] + my_map.get_axis_x();
		point[i].y = _center[1] + move[i][1] + my_map.get_axis_y();
	}

	return point;
}

//public
void Tank::tank_unshow(WallMap my_map)
{
	setPenColor(EMPTY);
	setBrushColor(WHITE);
	setBrushStyle(BRUSH_STYLE_SOLID);
	polygon(_get_point(my_map), 4);
}

void Tank::tank_show(WallMap my_map,ACL_Color color)
{
	setPenColor(EMPTY);
	setBrushColor(color);
	setBrushStyle(BRUSH_STYLE_SOLID);
	polygon(_get_point(my_map), 4);
}

/**
  * @brief  随机生成center的位置
  * @param  my_map : wallmap
  * @retval random_center[2]
  */
int* random_coordinate(WallMap my_map)
{
	int random_c[2];
	
	random_c[0] = rand() % (my_map.get_length() - 1) * UNIT_LENGTH + UNIT_LENGTH / 2;

	random_c[1] = rand() % (my_map.get_width() - 1) * UNIT_LENGTH + UNIT_LENGTH / 2;

	return random_c;
}
