#include "bullet.h"

#define EXISTENCE_TIME 300	//  实际时长未知（定时器精度较差），视程序而定
#define RADIUS 8
#define BULLET_SPEED 6

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
	int angle = 0;
	ACL_Color color;
	for (angle = 0; angle < 360; angle += 5)
	{
		color = getPixel(center[0] + (int)((RADIUS)*cos(angle * PI / 180)),
			center[1] + (int)((RADIUS)*sin(angle * PI / 180)));
		if (color == TANK1_COLOR)
			return -1;
		if (color == TANK2_COLOR)
			return -2;
	}

	if (getPixel(center[0], center[1] - RADIUS) == BLACK)
		return 1;
	if (getPixel(center[0], center[1] + RADIUS) == BLACK)
		return 2;
	if (getPixel(center[0] - RADIUS, center[1]) == BLACK)
		return 3;
	if (getPixel(center[0] + RADIUS, center[1]) == BLACK)
		return 4;

	for (angle = 0; angle < 360; angle += 5)
	{
		if (getPixel(center[0] + (int)((RADIUS - 1) * cos(angle * PI / 180)),
			center[1] + (int)((RADIUS - 1) * sin(angle * PI / 180))) == BLACK)
			return 5;		//防止正好打到wallmap的corner(但是仍然判断不足，懒得再写了。。)
	}
	
	return 0;
}

//just judege the map
int Bullet::_bullet_judge(int* pre_center, int* next_center)	//0: NONE	1:UP	2:down		3:left		4:right
{
	memset(pre_center, 0, sizeof(pre_center));
	memset(next_center, 0, sizeof(next_center));
	_for_move(next_center);
	_assign_center(pre_center, _center);
	int center[2];
	int judge = 0, i = 0;
	for (i = 0; i <= _linear_v; i++)
	{

		center[0] = (_center[0] * (_linear_v - i) + next_center[0] * i) / _linear_v;
		center[1] = (_center[1] * (_linear_v - i) + next_center[1] * i) / _linear_v;
		judge = _bullet_state_judge(center);
		if (judge != 0)
			break;
		_assign_center(pre_center, center);
	}

	return judge;
}

void Bullet::_bullet_move(int judge, int* pre_center, int* next_center)
{
	if (judge == 0)
	{
		_assign_center(_center, next_center);
	}
	else if (judge == 1)
	{
		_angle = (360 - _angle) % 360;
		_center[0] = next_center[0];
		_center[1] = 2 * pre_center[1] - next_center[1];
	}
	else if (judge == 2)
	{
		_angle = (360 - _angle) % 360;
		_center[0] = next_center[0];
		_center[1] = 2 * pre_center[1] - next_center[1];
	}
	else if (judge == 3)
	{
		_angle = (540 - _angle) % 360;
		_center[0] = 2 * pre_center[0] - next_center[0];
		_center[1] = next_center[1];
	}
	else if (judge == 4)
	{
		_angle = (540 - _angle) % 360;
		_center[0] = 2 * pre_center[0] - next_center[0];
		_center[1] = next_center[1];
	}
	else if (judge == 5)
	{
		_angle = (_angle + 180) % 360;
		_center[0] = 2 * pre_center[0] - next_center[0];
		_center[1] = 2 * pre_center[1] - next_center[1];
	}
}

Bullet::Bullet(int user):
	SolidObject(user, GREY, 0, 0, 0, RADIUS, RADIUS, BULLET_SPEED, 0),
	_is_use(0),_survive_time(0)
{
}

void Bullet::init(int orient, POINT* tank_points)
{
	_is_use = 1;
	_survive_time = EXISTENCE_TIME;
	_angle = orient;

	_center[0] = (tank_points[0].x + tank_points[3].x) / 2 + (int)((RADIUS + 1.5) * cos(_angle * PI / 180));
	_center[1] = (tank_points[0].y + tank_points[3].y) / 2 + (int)((RADIUS + 1.5) * sin(_angle * PI / 180));
}

bool Bullet::is_exist()
{
	return _is_use;
}

int Bullet::pre_time()
{
	_bullet_unshow();
	int pre_center[2];
	int next_center[2];
	int judge = _bullet_judge(pre_center, next_center);
	if (judge < 0)
	{
		_is_use = 0;
		return judge;
	}
	if (--_survive_time == 0)
	{
		_is_use = 0;
		return 0;
	}
	_bullet_move(judge, pre_center, next_center);
	_bullet_show();
	return 0;
}

void Bullet::anti_bug()
{
	if (getPixel(_center[0], _center[1]) == BLACK)
	{
		_bullet_unshow();
		_for_move(_center);
		_for_move(_center);
	}
}
