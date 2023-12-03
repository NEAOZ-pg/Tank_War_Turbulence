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

//public
void Tank::tank_unshow()
{
	setPenColor(EMPTY);
	setBrushColor(WHITE);
	setBrushStyle(BRUSH_STYLE_SOLID);
	polygon(_points_symmetric(_point_coordinates()), 4);
}

void Tank::tank_show()
{
	setPenColor(EMPTY);
	setBrushColor(_color);
	setBrushStyle(BRUSH_STYLE_SOLID);
	POINTS points[4];
	polygon(_points_symmetric(_point_coordinates()), 4);
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
