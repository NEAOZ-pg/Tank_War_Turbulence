#ifndef __BULLET_H__
#define __BULLET_H__

#include <Windows.h>

#include "solid_object.h"
#include "acllib.h"

class Bullet :public SolidObject
{
private:
	int _is_use;	//1,using ,0 unused 
	int _survive_time;

private:
	void _bullet_unshow();
	void _bullet_show();
	int _bullet_state_judge(int* center);
	void _bullet_judge();

public:
	Bullet(int user);
	void init(int orient, POINT* tank_points);
	bool is_exist();
	void pre_time();
};

#endif