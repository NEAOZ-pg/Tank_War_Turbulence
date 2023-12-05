#include "bullet.h"

#define EXISTENCE_TIME 150	//  实际时长未知（定时器精度较差），视程序而定
#define RADIUS 8
#define BULLET_SPEED 5

void Bullet::_bullet_unshow()
{
	setPenColor(EMPTY);
	setBrushColor(WHITE);
	setBrushStyle(BRUSH_STYLE_SOLID);
	ellipse(_center[0] + _half_length, _center[1] + _half_width, _center[0] - _half_width, _center[1] - _half_width);
}

void Bullet::_bullet_show()
{
	setPenColor(EMPTY);
	setBrushColor(_color);
	setBrushStyle(BRUSH_STYLE_SOLID);
	ellipse(_center[0] + _half_length, _center[1] + _half_width, _center[0] - _half_width, _center[1] - _half_width);
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
	beginPaint();

	_bullet_unshow();
	if (--_survive_time == 0)
	{
		_is_use = 0;
		endPaint();
		return;
	}
	//JUDGE!!!
	move_for_per_time();
	_bullet_show();

	endPaint();
}
