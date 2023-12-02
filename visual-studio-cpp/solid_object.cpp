#include <Windows.h>
#include <math.h>
#include "solid_object.h"
#include "wall_map.h"
#include "acllib.h"

#define PI 3.14

SolidObject::SolidObject(int user, ACL_Color color, int center[], 
	int angle, int half_length, int half_width, int speed) :
	_user(user), _color(color), _angle(angle), _half_length(half_length), _half_width(half_width), _speed(speed)
{
	_center[0] = center[0];
	_center[1] = center[1];
}

SolidObject::~SolidObject()
{
}

// protected

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
POINT* SolidObject::_points_symmetric(POINT point)
{
	POINT points[4];

	points[0].x = point.x;
	points[0].y = point.y;
	points[1].x = (long)(point.x - 2 * _half_length * cos(_angle * PI / 180));
	points[1].y = (long)(point.y - 2 * _half_length * sin(_angle * PI / 180));
	points[2].x = 2 * _center[0] - points[0].x;
	points[2].y = 2 * _center[1] - points[0].y;
	points[3].x = 2 * _center[0] - points[1].x;
	points[3].y = 2 * _center[1] - points[1].y;

	return points;
}


/*
int SolidObject::judge_edge(int* new_center, WallMap my_map)
{
	//判断边界
	
	可以使用的变量：
	int new_center[2]	//相对于整张大图，即280 * 210，左上角为原点（0，0）
	int angle, int half_length, int half_width

	my_map.pixel_check(int x, int y) == white 即为此像素块不是边界（非白色可能是其他的子弹或者坦克，
																暂时不考虑，这个函数只对边界判断）
	可以判断边界的某个点是否是边界的条件

	返回值，0：不是边界，1，边界在上面撞到，2，边界在下面撞到
					3，边界在左面撞到，4，边界在下面撞到

	

	return 0;
}
*/
void SolidObject::move_per_time()
{
	_center[0] += (int)(cos(_angle) * 3);
	_center[1] += (int)(sin(_angle) * 3);
}

void SolidObject::rotate_per_time()
{
	_angle = (_angle + 3) / 360;
	//判断！
}

/**
  * @brief  判断SolidObject是否crash Map
  * @param  None
  * @retval 1:uncrash	0:crash
  */
