#include "solid_object.h"

//INIT

SolidObject::SolidObject()
{
	_user = -1;	
	_color = EMPTY;
	_center[0] = 0;
	_center[1] = 0;
	_angle = 0;
	_half_length = 0;
	_half_width = 0;
	_linear_v = 0;
	_angular_v = 0;
}

SolidObject::SolidObject(int user, ACL_Color color, int center0, int center1,
	int angle, int half_length, int half_width, int linear_v, int angular_v) :
	_user(user), _color(color), _angle(angle), _half_length(half_length), 
	_half_width(half_width), _linear_v(linear_v), _angular_v(angular_v)
{
	_center[0] = center0;
	_center[1] = center1;
}

SolidObject::~SolidObject()
{
}

// protected

/**
  * @brief  将center2赋值给center1
  * @param1	center1：赋入
  * @param2	center2：赋出
  * @retval None
  */
void SolidObject::_assign_center(int* center1, const int* center2)
{
	center1[0] = center2[0];
	center1[1] = center2[1];
}

/**
  * @brief  理想情况向前移动_center
  * @param1	new_center:理想情况移动后的值
  * @retval None
  */
void SolidObject::_for_move(int* new_center)
{
	new_center[0] = _center[0] + round((cos(_angle * PI / 180) * _linear_v));
	new_center[1] = _center[1] + round((sin(_angle * PI / 180) * _linear_v));
}

/**
  * @brief  理想情况向后移动_center
  * @param1	new_center:理想情况移动后的值
  * @retval None
  */
void SolidObject::_back_move(int* new_center)
{
	new_center[0] = _center[0] - round((cos(_angle * PI / 180) * _linear_v));
	new_center[1] = _center[1] - round((sin(_angle * PI / 180) * _linear_v));
}

/**
  * @brief  计算右方上角的点（相对_angle = 0)的坐标
  * @param  None
  * @retval 在画布坐标系下的坐标（x，y）
  */
POINT SolidObject::_point_coordinates(int* center, int angle)
{
	POINT coordiante =
	{
		center[0] + (long)round(_half_length * cos(angle * PI / 180) 
			+ _half_width * cos((angle + 90) * PI / 180)),
		center[1] + (long)round(_half_length * sin(angle * PI / 180)
			+ _half_width * sin((angle + 90) * PI / 180)),
	};
	return coordiante;
}

/**
  * @brief  根据右方上角的点坐标求出四角坐标
  * @param  右方上角的点坐标
  * @retval	points[4]{x,y} 在画布坐标系下的四角坐标
  */ 
void SolidObject::_points_symmetric(POINT *points, int *center, int angle)
{
	POINT point = _point_coordinates(center, angle);
	points[0].x = point.x;
	points[0].y = point.y;
	points[1].x = (long)round(point.x - 2 * _half_length * cos(angle * PI / 180));
	points[1].y = (long)round(point.y - 2 * _half_length * sin(angle * PI / 180));
	points[2].x = 2 * center[0] - points[0].x;
	points[2].y = 2 * center[1] - points[0].y;
	points[3].x = 2 * center[0] - points[1].x;
	points[3].y = 2 * center[1] - points[1].y;
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
int SolidObject::_judge_move_crash(int* next_center)
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

int SolidObject::_judge_rotate_crash(int next_angle)
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

int SolidObject::get_angle()
{
	return _angle;
}

/**
  * @brief  获取四角的坐标
  * @param  None
  * @retval None
  */
void SolidObject::get_points(POINT* points)
{
	_points_symmetric(points, _center, _angle);
}

/**
  * @brief  向前移动
  * @param  None
  * @retval None
  */
void SolidObject::move_for_per_time()
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
void SolidObject::move_back_per_time()
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
void SolidObject::rotate_CW_per_time()
{
	_angle += _angular_v;
	//_judge_rotate_crash(_angle + _angular_v);
}

/**
  * @brief  逆时针（counterclockwise）旋转
  * @param  None
  * @retval None
  */
void SolidObject::rotate_CCW_per_time()
{
	_angle -= _angular_v;
	//_judge_rotate_crash(_angle - _angular_v);
}

