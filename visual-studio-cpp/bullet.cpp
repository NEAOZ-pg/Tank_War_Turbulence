#include "bullet.h"

#define EXISTENCE_TIME 150	//  实际时长未知（定时器精度较差），视程序而定
#define RADIUS 8
#define BULLET_SPEED 5

void Bullet::_bullet_unshow()
{
	setPenColor(WHITE);
	setPenWidth(0);
	setBrushColor(WHITE);
	setBrushStyle(BRUSH_STYLE_SOLID);
	ellipse(_center[0] + RADIUS, _center[1] + RADIUS, _center[0] - RADIUS, _center[1] - RADIUS);
}

void Bullet::_bullet_show()
{
	setPenColor(WHITE); 
	setPenWidth(0);
	setBrushColor(_color);
	setBrushStyle(BRUSH_STYLE_SOLID);
	ellipse(_center[0] + RADIUS, _center[1] + RADIUS, _center[0] - RADIUS, _center[1] - RADIUS);
}

int Bullet::_bullet_state_judge(int* center)
{
	if (getPixel(center[0], center[1] - RADIUS) == BLACK)
		return 1;
	if (getPixel(center[0], center[1] + RADIUS) == BLACK)
		return 2;
	if (getPixel(center[0] - RADIUS, center[1]) == BLACK)
		return 3;
	if (getPixel(center[0] + RADIUS, center[1]) == BLACK)
		return 4;

	return 0;
}

//just judege the map
void Bullet::_bullet_judge()	//0: NONE	1:UP	2:down		3:left		4:right
{
	int next_center[2];
	_next_move(next_center);
	int i = 0;

	int pre_center[2];
	_assign_center(pre_center, _center);
	int center[2];
	int judge = 0;
	for (i = 0; i <= _speed; i++)
	{
		center[0] = (_center[0] * (_speed - i) + next_center[0] * i) / _speed;
		center[1] = (_center[1] * (_speed - i) + next_center[1] * i) / _speed;
		judge = _bullet_state_judge(center);
		if (judge != 0)
			break;
		_assign_center(pre_center, center);
	}
	if (judge == 0)
	{
		_assign_center(_center, next_center);
	}
	else if (judge == 1)
	{
		_angle = 180 - _angle;
		_center[0] = next_center[0];
		_center[1] = 2 * pre_center[1] - next_center[1];
	}
	else if (judge == 2)
	{
		_angle = 540 - _angle;
		_center[0] = next_center[0];
		_center[1] = 2 * pre_center[1] - next_center[1];
	}
	else if (judge == 3)
	{
		_angle = 360 - _angle;
		_center[0] = 2 * pre_center[0] - next_center[0];
		_center[1] = next_center[1];
	}
	else if (judge == 4)
	{
		_angle = 360 - _angle;
		_center[0] = 2 * pre_center[0] - next_center[0];
		_center[1] = next_center[1];
	}

}

Bullet::Bullet(int user):
	SolidObject(user, GREY, 0, 0, 0, RADIUS, RADIUS, BULLET_SPEED),
	_is_use(0),_survive_time(0)
{
}

void Bullet::init(int orient, POINT* tank_points)
{
	_is_use = 1;
	_survive_time = EXISTENCE_TIME;
	_angle = orient;

	_center[0] = (tank_points[0].x + tank_points[3].x) / 2;
	_center[1] = (tank_points[0].y + tank_points[3].y) / 2;
}

bool Bullet::is_exist()
{
	return _is_use;
}

void Bullet::pre_time()
{
	_bullet_unshow();
	if (--_survive_time == 0)
	{
		_is_use = 0;
		return;
	}
	_bullet_judge();

	//move_for_per_time();
	_bullet_show();

}
