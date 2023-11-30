#ifndef __TANK_H__
#define __TANK_H__

#include <Windows.h>

#include "solid_object.h"
#include "acllib.h"
#include "wall_map.h"

class Tank:public SolidObject
{
private:
	POINT* _get_point(WallMap my_map);

public:
	Tank(int user, int* center, int angle, int length, int width, int speed);
	~Tank();

	void tank_unshow(WallMap my_map);
	void tank_show(WallMap my_map, ACL_Color color);
};

int* random_coordinate(WallMap my_map);

#endif
