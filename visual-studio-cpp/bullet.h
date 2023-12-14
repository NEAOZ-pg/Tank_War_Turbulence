#ifndef __BULLET_H__
#define __BULLET_H__

#include <Windows.h>

#include "solid_object.h"
#include "acllib.h"
#include "tank.h"

class Bullet :public SolidObject
{
private:
	int _is_use;	//1,using ,0 unused 
	int _survive_time;

private:
	void _bullet_unshow();
	void _bullet_show();
	int _bullet_state_judge(int* center);
	int _bullet_judge(int* pre_center, int* next_center);
	void _bullet_move(int judge, int* pre_center, int* next_center);

public:
	Bullet(int user);
	void init(int orient, POINT* tank_points);
	void clear();
	bool is_exist();
	int pre_time();
	void anti_bug();
};

#endif