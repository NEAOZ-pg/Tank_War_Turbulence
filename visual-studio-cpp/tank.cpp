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
  * @brief  ����̹���ڹܵ��ĸ��ǵ�ַ
  * @param  point:���ڴ���ڹ��ĸ���λ��
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
  * @brief  �ж�ĳһ״̬tank�Ƿ���ײ
  * @param  points����״̬���ĸ��ǵ�����
  * @retval 1��crash  2��uncrash
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
  * @brief  �ж�̹��ǰ���ƶ������ı�_center
  * @param  next_center���������һ��λ��
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
  * @brief  �ж�̹����ת�����ı�_angle
  * @param  next_angle���������һ����תλ��
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

	//��tank�ĽǶ�����������»ع�Ϊ_angular_v�ı���
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
  * @brief  �����һ��̹��λ����ʾ
  * @param  None
  * @retval None
  */
void Tank::tank_unshow()
{
	setPenColor(WHITE);
	setPenWidth(0);
	setBrushColor(WHITE);
	setBrushStyle(BRUSH_STYLE_SOLID);
	//����̹�˻���
	POINT points[4];
	_points_symmetric(points, _center, _angle);
	polygon(points, 4);
	//����̹���ڹܣ���һ�ο��ܲ�������ȫ��
	polygon(_points_cannon(points), 4);
}

/**
  * @brief  ̹��λ����ʾ
  * @param  None
  * @retval None
  */
void Tank::tank_show()
{
	setPenColor(EMPTY);
	setPenWidth(0);
	setBrushColor(_color);
	setBrushStyle(BRUSH_STYLE_SOLID);
	//��ʾ̹�˻���
	POINT points[4];
	_points_symmetric(points, _center, _angle);
	polygon(points, 4);
	//��ʾ̹���ڹܣ�͵���˾Ͷ��Ǻ�ɫ��
	setBrushColor(RED);
	polygon(_points_cannon(points), 4);
}

/**
  * @brief  ��ǰ�ƶ�
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
  * @brief  ����ƶ�
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
  * @brief  ˳ʱ�루clockwise����ת
  * @param  None
  * @retval None
  */
void Tank::rotate_CW_per_time()
{
	//_angle += _angular_v;
	_judge_rotate_crash(_angle + _angular_v);
}

/**
  * @brief  ��ʱ�루counterclockwise����ת
  * @param  None
  * @retval None
  */
void Tank::rotate_CCW_per_time()
{
	//_angle -= _angular_v;
	_judge_rotate_crash(_angle - _angular_v);
}


/**
  * @brief  �������tank��λ��,λ��ÿһ����ͼ�������
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
  * @brief  �������angle(0,90,180,270)
  * @param  None
  * @retval angle
  */
int Tank::random_angle()
{
	return rand() % 4 * 90;
}

/**
  * @brief  ��ʾtank����
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
  * @brief  ���
  * @param  None
  * @retval None
  */
void Tank::clear_score()
{
	tank1_green_score = 0;
	tank2_blue_score = 0;
}
