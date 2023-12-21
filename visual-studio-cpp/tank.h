#ifndef __TANK_H__
#define __TANK_H__

#include <Windows.h>

#include "solid_object.h"
#include "acllib.h"
#include "wall_map.h"

#define TANK1_COLOR GREEN
#define TANK2_COLOR BLUE

extern int tank1_green_score;
extern int tank2_blue_score;

class Tank :public SolidObject
{
public:
	Tank();
	Tank(int user, ACL_Color color, int* center, int angle);
	~Tank();

private:
	POINT* _points_cannon(POINT* points);
	int _judge_state(POINT* points);
	int _judge_move_crash(int* next_center);
	int _judge_rotate_crash(int next_angle);

public:
	void tank_unshow();
	void tank_show();
	void move_for_per_time();
	void move_back_per_time();
	void rotate_CW_per_time();
	void rotate_CCW_per_time();

	static int* random_coordinate(WallMap my_map);
	static int random_angle();
	static void show_score();
	static void clear_score();
};

#endif
