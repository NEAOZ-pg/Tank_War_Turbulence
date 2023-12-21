#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS

#include "tank.h"

#include <stdlib.h>
#include "global_param.h"

#define TANK_LENGTH		25
#define TANK_WIDTH		15
#define TANK_LINEAR_V	9
#define TANK_ANGULAR_V	15

int tank1_green_score = 0;
int tank2_blue_score = 0;

//INIT

Tank::Tank()
{
}

Tank::Tank(int user, ACL_Color color, int* center, int angle) :
	SolidObject(user, color, center[0], center[1], angle, TANK_LENGTH, TANK_WIDTH, TANK_LINEAR_V, TANK_ANGULAR_V)
{
}

Tank::~Tank()
{
}

//private

/**
  * @brief  计算坦克炮管的四个角地址
  * @param  point:用于存放炮管四个角位置
  * @retval None
  */
POINT* Tank::_points_cannon(POINT* points)
{
	POINT cannon[4];
	cannon[0].x = (points[0].x * 2 + points[3].x) / 3;
	cannon[0].y = (points[0].y * 2 + points[3].y) / 3;
	cannon[1].x = (points[3].x * 2 + points[0].x) / 3;
	cannon[1].y = (points[3].y * 2 + points[0].y) / 3;
	cannon[2].x = _center[0] + (cannon[1].x - cannon[0].x) / 2;
	cannon[2].y = _center[1] + (cannon[1].y - cannon[0].y) / 2;
	cannon[3].x = _center[0] + (cannon[0].x - cannon[1].x) / 2;
	cannon[3].y = _center[1] + (cannon[0].y - cannon[1].y) / 2;
	return cannon;
}

/**
  * @brief  判断某一状态tank是否碰撞
  * @param  points：改状态的四个角的坐标
  * @retval 1：crash  2：uncrash
  */
int Tank::_judge_state(POINT* points)
{
	int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
	int x = 0, y = 0;
	int i = 0, j = 0;
	for (i = 0; i < 4; i++)
	{
		x1 = points[i % 4].x;
		y1 = points[i % 4].y;
		x2 = points[(i + 1) % 4].x;
		y2 = points[(i + 1) % 4].y;
		for (j = 0; j < 10; j++)
		{
			x = round((x1 * j + x2 * (10 - j)) / 10.0);
			y = round((y1 * j + y2 * (10 - j)) / 10.0);
			if (getPixel(x, y) != WHITE)
				return 1;
		}
	}
	return 0;
}

/**
  * @brief  判断坦克前后移动，并改变_center
  * @param  next_center：理想的下一个位置
  * @retval None
  */
int Tank::_judge_move_crash(int* next_center)
{
	int i = 0;
	int state_center[2];
	int pre_center[4];
	_assign_center(state_center, _center);
	_assign_center(pre_center, _center);
	POINT state_points[4];
	for (i = 1; i <= _linear_v; i++)
	{
		state_center[0] = round((_center[0] * (_linear_v - i) 
			+ next_center[0] * i) / (double)_linear_v);
		state_center[1] = round((_center[1] * (_linear_v - i)
			+ next_center[1] * i) / (double)_linear_v);
		_points_symmetric(state_points, state_center, _angle);
		if (_judge_state(state_points))
			break;
		_assign_center(pre_center, state_center);
	}
	_assign_center(_center, pre_center);
	return 0;
}

/**
  * @brief  判断坦克旋转，并改变_angle
  * @param  next_angle：理想的下一个旋转位置
  * @retval None
  */
int Tank::_judge_rotate_crash(int next_angle)
{
	int i = 0;
	int state_angle = _angle;
	int pre_angle = _angle;
	POINT state_points[4];
	int add_or_sub = next_angle - _angle > 0 ? 1 : -1;
	int judge = 0;
	for (i = 0; i <= _angular_v; i++)
	{
		state_angle = state_angle + add_or_sub;
		_points_symmetric(state_points, _center, state_angle);
		if (judge = _judge_state(state_points))
			break;
		pre_angle = state_angle;
	}

	//让tank的角度在正常情况下回归为_angular_v的倍数
	int c_angle = state_angle, cc_angle = state_angle;
	state_angle = state_angle + add_or_sub;
	_points_symmetric(state_points, _center, state_angle);
	if (!(judge || _judge_state(state_points)))
		while (1)
		{
			if (c_angle / _angular_v * _angular_v == c_angle)
			{
				_points_symmetric(state_points, _center, c_angle);
				if (!_judge_state(state_points))
				{
					_angle = c_angle;
					break;
				}
			}
			else if(cc_angle / _angular_v * _angular_v == cc_angle)
			{
				_points_symmetric(state_points, _center, cc_angle);
				if (!_judge_state(state_points))
				{
					_angle = cc_angle;
					break;
				}
			}
			++c_angle;
			--cc_angle;
		}
	return 0;
}

//public

/**
  * @brief  清除上一次坦克位置显示
  * @param  None
  * @retval None
  */
void Tank::tank_unshow()
{
	setPenColor(WHITE);
	setPenWidth(0);
	setBrushColor(WHITE);
	setBrushStyle(BRUSH_STYLE_SOLID);
	//擦除坦克机身
	POINT points[4];
	_points_symmetric(points, _center, _angle);
	polygon(points, 4);
	//擦除坦克炮管（上一次可能擦除不完全）
	polygon(_points_cannon(points), 4);
}

/**
  * @brief  坦克位置显示
  * @param  None
  * @retval None
  */
void Tank::tank_show()
{
	setPenColor(EMPTY);
	setPenWidth(0);
	setBrushColor(_color);
	setBrushStyle(BRUSH_STYLE_SOLID);
	//显示坦克机身
	POINT points[4];
	_points_symmetric(points, _center, _angle);
	polygon(points, 4);
	//显示坦克炮管（偷懒了就都是红色）
	setBrushColor(RED);
	polygon(_points_cannon(points), 4);
}

/**
  * @brief  向前移动
  * @param  None
  * @retval None
  */
void Tank::move_for_per_time()
{
	//_for_move(_center);

	int next_center[2];
	_for_move(next_center);
	_judge_move_crash(next_center);
}

/**
  * @brief  向后移动
  * @param  None
  * @retval None
  */
void Tank::move_back_per_time()
{
	//_back_move(_center);

	int next_center[2];
	_back_move(next_center);
	_judge_move_crash(next_center);
}

/**
  * @brief  顺时针（clockwise）旋转
  * @param  None
  * @retval None
  */
void Tank::rotate_CW_per_time()
{
	//_angle += _angular_v;
	_judge_rotate_crash(_angle + _angular_v);
}

/**
  * @brief  逆时针（counterclockwise）旋转
  * @param  None
  * @retval None
  */
void Tank::rotate_CCW_per_time()
{
	//_angle -= _angular_v;
	_judge_rotate_crash(_angle - _angular_v);
}


/**
  * @brief  随机生成tank的位置,位于每一个地图块的中央
  * @param  my_map : wallmap
  * @retval random_center[2]
  */
int* Tank::random_coordinate(WallMap my_map)
{
	int random_c[2];
	do
	{
		random_c[0] = rand() % (my_map.get_length() - 1) * UNIT_LENGTH + UNIT_LENGTH / 2 + my_map.get_axis_x();
		random_c[1] = rand() % (my_map.get_width() - 1) * UNIT_LENGTH + UNIT_LENGTH / 2 + my_map.get_axis_y();
	} while (getPixel(random_c[0], random_c[1]) != WHITE);

	return random_c;
}

/**
  * @brief  随机生成angle(0,90,180,270)
  * @param  None
  * @retval angle
  */
int Tank::random_angle()
{
	return rand() % 4 * 90;
}

/**
  * @brief  显示tank分数
  * @param  None
  * @retval None
  */
void Tank::show_score()
{
	putImage(&img_Tankblue, 800, 700);
	putImage(&img_Tankgreen, 300, 700);

	setTextColor(GREY);
	setTextBkColor(WHITE);
	setTextSize(32);
	setTextFont(font_name);

	//int -> string
	char int_str[10];
	itoa(tank1_green_score, int_str, 10);
	paintText(420, 740, int_str);

	itoa(tank2_blue_score, int_str, 10);
	paintText(760, 740, int_str);
}

/**
  * @brief  清除
  * @param  None
  * @retval None
  */
void Tank::clear_score()
{
	tank1_green_score = 0;
	tank2_blue_score = 0;
}
