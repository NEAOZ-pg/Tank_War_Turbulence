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

/*
int SolidObject::_judge_crash()
{
	POINT points[4];
	_points_symmetric((points));


	//判断除了撞上子弹的一切。
	/*
	可以使用的变量：
	int new_center[2]	//相对window窗口，即在windowinit（）创建的窗口左上角为原点（0，0）
	int angle, int half_length, int half_width（可能用不到）

	上面的两句，获得的points 结构体长这样
	typedef struct tagPOINT
	{
		LONG  x;
		LONG  y;
	} POINT,
	存四个角的x和y。
	顺序（当坦克朝向右边的时候）：按照逆时针：右上角，左上角，左下角，右下角。

	ACL_Color getPixel(int x, int y);（函数原型在acclib.h中
	返回颜色，只要不是白色（什么都没有）和（GREY：子弹）都算是碰到边界
											（子弹暂时不考虑）

	返回值，0：不是边界，1，边界在上面撞到，2，边界在下面撞到
					3，边界在左面撞到，4，边界在下面撞到


	return 0;
}*/
int Tank::_judge_move_crash(int* next_center)
{
	ACL_Color target;
	POINT origin_points[4];
	_points_symmetric(origin_points, _center, _angle);
	int process_center[2];//循环过程中心坐标
	POINT process_point[4];//循环过程四个角
	POINT next_points[4];
	_points_symmetric(next_points, next_center, _angle);
	int i, j;//建立循环
	float coefficient;
	int slope;//斜率
	int sign;//正负
	if (next_center[0] >= _center[0])
		sign = 1;
	else sign = -1;
	if (next_center[0] != _center[0])
	{
		coefficient = (next_center[1] - _center[1]) / (next_center[0] - _center[0]);
		if (next_center[0] > _center[0])
			slope = 1;
		else slope = -1;
	}
	else {
		slope = 0;
		if (next_center[1] > _center[1])
			coefficient = 1;
		else coefficient = -1;
	}//确定斜率
	process_center[0] = _center[0];
	process_center[1] = _center[1];
	for (j = 0; j < 4; ++j)
	{
		process_point[j].x = origin_points[j].x;
		process_point[j].y = origin_points[j].y;
	}//先把过程变量与小车初始状态对齐
	for (i = 0; i <= abs(next_center[0] - _center[0]); ++i)
	{
		process_center[0] = process_center[0] + slope;
		process_center[1] = process_center[1] + sign * (int)(coefficient);
		for (j = 0; j < 4; ++j)
		{
			process_point[j].x = process_point[j].x + slope;
			process_point[j].y = process_point[j].y + sign * (int)(coefficient);
			target = getPixel(process_point[j].x, process_point[j].y);
			if ((target == BLACK) || (target == BLUE) || (target == GREEN))
			{
				_center[0] = process_center[0] - slope;
				_center[1] = process_center[1] - sign * (int)(coefficient);
				return 1;
			}
		}
	}
	_center[0] = next_center[0];
	_center[1] = next_center[1];//中途没有撞墙，移动正常，传递位置
	return 0;
}

int Tank::_judge_rotate_crash(int next_angle)
{
	//_angular_v=next_angle-_angle;
	//这个函数只模拟旋转一次十度的情况
	//_angle,_center,origin_points已知
	ACL_Color target;
	POINT origin_points[4];
	_points_symmetric(origin_points, _center, _angle);
	POINT process_points[5];//用于取点判断
	POINT judge_points[5];//用于判断边的坐标
	POINT next_points[4];
	_points_symmetric(next_points, _center, next_angle);
	int sign[4];//取点方向
	int coefficient[4], slope[4];//y方向改变量，x方向改变量；
	int i, j;//循环控制变量
	for (i = 0; i < 5; ++i)
	{
		if (i == 4)
		{
			judge_points[i].x = next_points[0].x;
			judge_points[i].y = next_points[0].y;
			break;
		}
		judge_points[i].x = next_points[i].x;
		judge_points[i].y = next_points[i].y;
	}
	//
	for (i = 0; i < 4; ++i)
	{
		if (judge_points[i + 1].x >= judge_points[i].x)
			sign[i] = 1;
		else sign[i] = -1;
		if (next_points[i].x != next_points[i + 1].x)
		{
			coefficient[i] = (next_points[i + 1].y - next_points[i].y) / (next_points[i + 1].x - next_points[i].x);
			if (next_points[i + 1].x > next_points[i].x)
				slope[i] = 1;
			else slope[i] = -1;
		}
		else {
			slope[i] = 0;
			if (next_points[i + 1].y > next_points[i].y)
				coefficient[i] = 1;
			else coefficient[i] = -1;
		}//确定斜率
	}

	for (j = 0; j < 5; ++j)
	{
		process_points[j].x = judge_points[j].x;
		process_points[j].y = judge_points[j].y;
	}//先把过程变量与小车初始状态对齐

	for (i = 0; i <= 4; ++i)
	{
		for (j = 0; j <= abs(process_points[i + 1].x - process_points[i].x); ++j)
		{
			process_points[i].x = process_points[i].x + slope[i];
			process_points[i].y = process_points[i].y + sign[i] * (int)(coefficient[i]);
			target = getPixel(process_points[i].x, process_points[i].y);
			if ((target == BLACK) || (target == BLUE) || (target == GREEN))
				return 1;
		}
	}
	_angle = next_angle;
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
	_angle += _angular_v;
	//_judge_rotate_crash(_angle + _angular_v);
}

/**
  * @brief  逆时针（counterclockwise）旋转
  * @param  None
  * @retval None
  */
void Tank::rotate_CCW_per_time()
{
	_angle -= _angular_v;
	//_judge_rotate_crash(_angle - _angular_v);
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
	}while(getPixel(random_c[0],random_c[1]) != WHITE);

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
