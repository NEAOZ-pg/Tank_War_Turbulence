#include "bullet.h"

#define EXISTENCE_TIME 300	//实际时长未知（定时器精度较差），视程序而定
#define RADIUS 8
#define BULLET_SPEED 6

//INIT

Bullet::Bullet(int user) :
	SolidObject(user, GREY, 0, 0, 0, RADIUS, RADIUS, BULLET_SPEED, 0),
	_is_use(0), _survive_time(0)
{
}

//private

/**
  * @brief  清除上一次的子弹位置显示
  * @param  None
  * @retval None
  */
void Bullet::_bullet_unshow()
{
	setPenColor(WHITE);
	setPenWidth(0);
	setBrushColor(WHITE);
	setBrushStyle(BRUSH_STYLE_SOLID);
	ellipse(_center[0] + RADIUS, _center[1] + RADIUS, _center[0] - RADIUS, _center[1] - RADIUS);
}

/**
  * @brief  判断当前位置子弹有无撞墙
  * @param  *center：预设预设子弹的x，y位置
  * @retval 1：UP	2：DOWN	3：LEFT	4：RIGHT
  				-1：TANK1（USER1）	-2：TANK2（USER2）
				0：None
  */
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

	if (getPixel(center[0], center[1] - RADIUS + 1) == BLACK)
		return 1;
	if (getPixel(center[0], center[1] + RADIUS - 1) == BLACK)
		return 2;
	if (getPixel(center[0] - RADIUS + 1, center[1]) == BLACK)
		return 3;
	if (getPixel(center[0] + RADIUS - 1, center[1]) == BLACK)
		return 4;
	
	return 0;
}

/**
  * @brief  判断子弹在运动到下一个位置过程中有无撞墙
  * @param1 *pre_center：先前的子弹x,y位置
  * @param2 *next_center：下一次的子弹理论的x,y位置
  * @retval 1：UP	2：DOWN	3：LEFT	4：RIGHT
				-1：TANK1（USER1）	-2：TANK2（USER2）
				0：None
  */
int Bullet::_bullet_judge(int* pre_center, int* next_center)	//0: NONE	1:UP	2:down		3:left		4:right
{
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

/**
  * @brief  根据judge值移动子弹_center和反射_angle
  * @param1 judge：1：UP	2：DOWN	3：LEFT	4：RIGHT
				   	-1：TANK1（USER1）	-2：TANK2（USER2）
				   	0：None
  * @param2 *pre_center：先前的子弹x,y位置
  * @param3 *next_center：下一次的子弹理论的x,y位置
  * @retval 1：UP	2：DOWN	3：LEFT	4：RIGHT
				-1：TANK1（USER1）	-2：TANK2（USER2）
				0：None
  */
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
}

/**
  * @brief  针对子弹刚发射时的小bug修复（还存在其他bug，称之为小彩蛋或者“有意为之”的逃课技巧）
  * @param  None
  * @retval None
  */
void Bullet::_first_shoot_anti_bug()
{
	if (_survive_time = 300)
	{
		if (getPixel(_center[0], _center[1]) == BLACK)
		{
			_angle = (_angle + 180) / 2;
			_for_move(_center);
		}
	}
}

//public

/**
  * @brief  子弹发射时的启用初始化
  * @param1 orient：tank朝向
  * @param2 *tank_points：tank四角坐标
  * @retval None
  */
void Bullet::init(int orient, POINT* tank_points)
{
	_is_use = 1;
	_survive_time = EXISTENCE_TIME;
	_angle = orient;

	_center[0] = (tank_points[0].x + tank_points[3].x) / 2 + (int)((RADIUS + 1.5) * cos(_angle * PI / 180));
	_center[1] = (tank_points[0].y + tank_points[3].y) / 2 + (int)((RADIUS + 1.5) * sin(_angle * PI / 180));
}

/**
  * @brief  游戏结束时子弹的弃用
  * @param  None
  * @retval None
  */
void Bullet::clear()
{
	_is_use = 0;
	_survive_time = 0;
	_bullet_unshow();
}

/**
  * @brief  子弹是否活着
  * @param  None
  * @retval 1：活着	0：死了
  */
bool Bullet::is_exist()
{
	return _is_use;
}

/**
  * @brief  子弹每一次的移动，并显示子弹在window上
  * @param  None
  * @retval None
  */
int Bullet::pre_time()
{
	_first_shoot_anti_bug();
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
	bullet_show();
	return 0;
}


/**
  * @brief  子弹位置显示
  * @param  None
  * @retval None
  */
void Bullet::bullet_show()
{
	setPenColor(WHITE);
	setPenWidth(0);
	setBrushColor(_color);
	setBrushStyle(BRUSH_STYLE_SOLID);
	ellipse(_center[0] + RADIUS, _center[1] + RADIUS, _center[0] - RADIUS, _center[1] - RADIUS);
}

