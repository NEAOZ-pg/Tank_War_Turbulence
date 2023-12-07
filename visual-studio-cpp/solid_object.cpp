#include "solid_object.h"

#define ANGULAR_V 10

SolidObject::SolidObject()
{
}

SolidObject::SolidObject(int user, ACL_Color color, int center0, int center1,
	int angle, int half_length, int half_width, int speed) :
	_user(user), _color(color), _angle(angle), _half_length(half_length), _half_width(half_width), _speed(speed)
{
	_center[0] = center0;
	_center[1] = center1;
}

SolidObject::~SolidObject()
{
}

int SolidObject::get_angle()
{
	return _angle;
}

POINT* SolidObject::get_points()
{
	POINT* points = new POINT[4];
	_points_symmetric(points);
	return points;
}

// protected

void SolidObject::_assign_center(int* center1, const int* center2)
{
	center1[0] = center2[0];
	center1[1] = center2[1];
}

void SolidObject::_next_move(int* new_center)
{
	new_center[0] = _center[0] + (int)(_half_length * cos(_angle * PI / 180)
		+ _half_width * cos((_angle + 90) * PI / 180));
	new_center[1] = _center[1] + (int)(_half_length * sin(_angle * PI / 180)
		+ _half_width * sin((_angle + 90) * PI / 180));
}

/**
  * @brief  计算右方上角的点（_angle = 0)的坐标
  * @param  None
  * @retval 在画布坐标系下的坐标（x，y）
  */
POINT SolidObject::_point_coordinates()
{
	POINT coordiante =
	{
		_center[0] + (long)(_half_length * cos(_angle * PI / 180) 
			+ _half_width * cos((_angle + 90) * PI / 180)),
		_center[1] + (long)(_half_length * sin(_angle * PI / 180) 
			+ _half_width * sin((_angle + 90) * PI / 180)),
	};
	return coordiante;
}

/**
  * @brief  根据右方上角的点坐标求出四角坐标
  * @param  右方上角的点坐标
  * @retval	points[4]{x,y} 在画布坐标系下的四角坐标
  */
void SolidObject::_points_symmetric(POINT *points)
{
	POINT point = _point_coordinates();
	points[0].x = point.x;
	points[0].y = point.y;
	points[1].x = (long)(point.x - 2 * _half_length * cos(_angle * PI / 180));
	points[1].y = (long)(point.y - 2 * _half_length * sin(_angle * PI / 180));
	points[2].x = 2 * _center[0] - points[0].x;
	points[2].y = 2 * _center[1] - points[0].y;
	points[3].x = 2 * _center[0] - points[1].x;
	points[3].y = 2 * _center[1] - points[1].y;
}


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
	*/

	return 0;
}

//public

void SolidObject::move_for_per_time()
{
	if (!_judge_crash())
	{
		_center[0] += (int)(cos(_angle * PI / 180) * _speed);
		_center[1] += (int)(sin(_angle * PI / 180) * _speed);
	}
}

void SolidObject::move_back_per_time()
{
	if (!_judge_crash())
	{
		_center[0] -= (int)(cos(_angle * PI / 180) * _speed);
		_center[1] -= (int)(sin(_angle * PI / 180) * _speed);
	}
}

void SolidObject::rotate_CW_per_time()
{
	_angle = (_angle + ANGULAR_V) % 360;
	//判断！
}

void SolidObject::rotate_CCW_per_time()
{
	_angle = (_angle - ANGULAR_V) % 360;
	//判断！
}

/**
  * @brief  判断SolidObject是否crash Map
  * @param  None
  * @retval 1:uncrash	0:crash
  */
