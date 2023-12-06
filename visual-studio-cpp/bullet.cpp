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

//just judege the map
int Bullet::_bullet_judge()	//0: NONE	1:UP	2:down		3:left		4:right
{
	int new_center[2] =
	{
		 _center[0] + (int)(_half_length * cos(_angle * PI / 180)
			+ _half_width * cos((_angle + 90) * PI / 180)),
		_center[1] + (int)(_half_length * sin(_angle * PI / 180)
			+ _half_width * sin((_angle + 90) * PI / 180)),
	};

	if (getPixel(new_center[0], new_center[1] - RADIUS + 3) == BLACK)
		return 1;
	if (getPixel(new_center[0], new_center[1] + RADIUS + 3) == BLACK)
		return 2;
	if (getPixel(new_center[0] - RADIUS + 2, new_center[1]) == BLACK)
		return 3;
	if (getPixel(new_center[0] + RADIUS - 2, new_center[1]) == BLACK)
		return 4;
	return 0;
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
	int judge = _bullet_judge();
	if (judge == 1)
		_angle = 540 - _angle;
	else if (judge == 2)
		_angle = 180 - _angle;
	else if (judge == 3)
		_angle = 360 - _angle;
	else if (judge == 4)
		_angle = 360 - _angle;

	move_for_per_time();
	_bullet_show();

}
