#include "solid_object.h"

SolidObject::SolidObject()
{

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

int SolidObject::get_angle()
{
	return _angle;
}

POINT* SolidObject::get_points()
{
	POINT* points = new POINT[4];
	_points_symmetric(points, _center, _angle);
	return points;
}

// protected

void SolidObject::_assign_center(int* center1, const int* center2)
{
	center1[0] = center2[0];
	center1[1] = center2[1];
}

void SolidObject::_for_move(int* new_center)
{
	new_center[0] = _center[0] + (int)(cos(_angle * PI / 180) * _linear_v);
	new_center[1] = _center[1] + (int)(sin(_angle * PI / 180) * _linear_v);
}

void SolidObject::_back_move(int* new_center)
{
	new_center[0] = _center[0] - (int)(cos(_angle * PI / 180) * _linear_v);
	new_center[1] = _center[1] - (int)(sin(_angle * PI / 180) * _linear_v);
}

/**
  * @brief  计算右方上角的点（_angle = 0)的坐标
  * @param  None
  * @retval 在画布坐标系下的坐标（x，y）
  */
POINT SolidObject::_point_coordinates(int* center, int angle)
{
	POINT coordiante =
	{
		center[0] + (long)(_half_length * cos(angle * PI / 180) 
			+ _half_width * cos((angle + 90) * PI / 180)),
		center[1] + (long)(_half_length * sin(angle * PI / 180) 
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
	points[1].x = (long)(point.x - 2 * _half_length * cos(angle * PI / 180));
	points[1].y = (long)(point.y - 2 * _half_length * sin(angle * PI / 180));
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

int SolidObject::_judge_move_crash(int *next_center)
{
	ACL_Color m;
	POINT origin_points[4];
	_points_symmetric(origin_points, _center, _angle);
	int process_center[2];//循环过程中心坐标
	POINT process_point[4];//循环过程四个角
	POINT next_points[4];
	_points_symmetric(next_points, next_center, _angle);
	int i, j;//建立循环
	int coefficient, slope;//斜率
	if (next_center[0] != _center[0])
	{
		slope = 1;
		coefficient = (next_center[1] - _center[1]) / (next_center[0] - _center[0]);
	}
	else {
		slope = 0;
		coefficient = 1;
	}
	process_center[0] = _center[0];
	process_center[1] = _center[1];
	for (j = 0; j < 4; ++j)
	{
		process_point[j].x = origin_points[j].x;
		process_point[j].y = origin_points[j].y;
	}//先把过程变量与小车初始状态对齐
	for (i = 0; i <= (int)((next_center[0] - _center[0])); ++i)
	{
		process_center[0] = _center[0] + slope;
		process_center[1] = _center[1] + (int)(coefficient);
		for (j = 0; j < 4; ++j)
		{
			process_point[j].x = origin_points[j].x + slope;
			process_point[j].y = origin_points[j].y + (int)(coefficient);
			m = getPixel(process_point[j].x, process_point[j].y);
			if (m != WHITE)
			{
				_center[0] = process_center[0] - 1;//_assign_center
				_center[1] = process_center[1] - (int)(coefficient);//第一次检测到撞墙的时候就是临界状态（之前的状态都是正常的情况下）
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
	//_angle,_center,origin_points已知
	ACL_Color m;
	POINT origin_points[4];
	_points_symmetric(origin_points, _center, _angle);
	POINT process_point[4];//过程中相对坐标原点的坐标
	POINT relative_point[4];//过程中相对中心的坐标
	POINT next_points[4];
	_points_symmetric(next_points, _center, next_angle);
	int i, j, k;//循环控制变量
	const float unit = 3.14 / 18;//最小旋转单位
	int time = (int)((next_angle - _angle) / 10);
	for (j = 0; j < 4; ++j)
	{
		process_point[j].x = origin_points[j].x;
		process_point[j].y = origin_points[j].y;
		relative_point[j].x = process_point[j].x - _center[0];
		relative_point[j].y = process_point[j].y - _center[1];
	}//先把过程变量与小车初始状态对齐
	for (i = 0; i < time; ++i)
	{
		for (j = 0; j < 4; ++j)
		{
			relative_point[j].x = (int)(relative_point[j].x * cos(unit) - relative_point[j].y * sin(unit));
			relative_point[j].y = (int)(relative_point[j].x * sin(unit) + relative_point[j].y * cos(unit));
			m = getPixel(relative_point[j].x + origin_points[j].x, relative_point[j].y + origin_points[j].y);
			if (m != WHITE)
			{
				for (k = 0; k < 4; ++k)
				{
					origin_points[k].x = relative_point[j].x + origin_points[j].x;
					origin_points[k].y = relative_point[j].y + origin_points[j].y;
					return 1;
				}
			}
		}
	}
	for (j = 0; j < 4; ++j)
	{
		origin_points[j].x = next_points[j].x;
		origin_points[j].y = next_points[j].y;
	}
	return 0;
}

//public

void SolidObject::move_for_per_time()
{
	//_for_move(_center);

	int next_center[2];
	_for_move(next_center);
	_judge_move_crash(next_center);
}

void SolidObject::move_back_per_time()
{
	//_back_move(_center);

	int next_center[2];
	_back_move(next_center);
	_judge_move_crash(next_center);
}

void SolidObject::rotate_CW_per_time()
{
	_angle += _angular_v;
	_judge_rotate_crash(_angle + _angular_v);
}

void SolidObject::rotate_CCW_per_time()
{
	_angle -= _angular_v;
	_judge_rotate_crash(_angle - _angular_v);
}

/**
  * @brief  判断SolidObject是否crash Map
  * @param  None
  * @retval 1:uncrash	0:crash
  */
