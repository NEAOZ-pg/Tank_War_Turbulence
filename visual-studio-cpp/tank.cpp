#include <Windows.h>
#include <stdlib.h>

#include "tank.h"

#include "acllib.h"
#include "wall_map.h"

Tank::Tank(int user, ACL_Color color, int* center, int angle, int half_length, int half_width, int speed) :
	SolidObject(user, color, center, angle, half_length, half_width, speed)
{
}

Tank::~Tank()
{
}

//private

POINT* Tank::_points_cannon(POINT* points)
{
	POINT cannon[3];
	cannon[0].x = (points[0].x * 2 + points[3].x) / 3;
	cannon[0].y = (points[0].y * 2 + points[3].y) / 3;
	cannon[1].x = (points[3].x * 2 + points[0].x) / 3;
	cannon[1].y = (points[3].y * 2 + points[0].y) / 3;
	cannon[2].x = _center[0];
	cannon[2].y = _center[1];
	return cannon;
}

//public
void Tank::tank_unshow()
{
	setPenColor(EMPTY);
	setBrushColor(WHITE);
	setBrushStyle(BRUSH_STYLE_SOLID);
	POINT points[4];
	_points_symmetric(points, _point_coordinates());
	polygon(points, 4);
}

void Tank::tank_show()
{
	setPenColor(EMPTY);
	setBrushColor(_color);
	setBrushStyle(BRUSH_STYLE_SOLID);
	POINT points[4];
	_points_symmetric(points, _point_coordinates());
	polygon(points, 4);
	setBrushColor(WHITE);
	polygon(_points_cannon(points), 3);
}

/**
  * @brief  随机生成center的位置
  * @param  my_map : wallmap
  * @retval random_center[2]
  */
int* random_coordinate(WallMap my_map)
{
	int random_c[2];
	do 
	{
		random_c[0] = rand() % (my_map.get_length() - 1) * UNIT_LENGTH + UNIT_LENGTH / 2 + my_map.get_axis_x();
		random_c[1] = rand() % (my_map.get_width() - 1) * UNIT_LENGTH + UNIT_LENGTH / 2 + my_map.get_axis_y();
	}while(getPixel(random_c[0],random_c[1]) != WHITE);

	return random_c;
}
