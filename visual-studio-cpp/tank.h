#ifndef __TANK_H__
#define __TANK_H__

#include <Windows.h>

#include "solid_object.h"
#include "acllib.h"
#include "wall_map.h"

class Tank:public SolidObject
{
private:

public:
	Tank(int user, ACL_Color color, int* center, int angle, int length, int width, int speed);
	~Tank();

	void tank_unshow();
	void tank_show();
};

int* random_coordinate(WallMap my_map);

#endif
