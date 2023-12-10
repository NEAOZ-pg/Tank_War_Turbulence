#ifndef __TANK_H__
#define __TANK_H__

#include <Windows.h>

#include "solid_object.h"
#include "acllib.h"
#include "wall_map.h"

#define TANK1_COLOR GREEN
#define TANK2_COLOR BLUE

class Tank:public SolidObject
{
private:
	POINT* _points_cannon(POINT* points);
public:
	Tank();
	Tank(int user, ACL_Color color, int* center, int angle);
	~Tank();

	void tank_unshow();
	void tank_show();
};

int* random_coordinate(WallMap my_map);
int random_angle();

#endif
