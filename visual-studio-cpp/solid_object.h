#ifndef __SOLID_OBJECT_H__
#define __SOLID_OBJECT_H__

#include <Windows.h>
#include <math.h>

#include "acllib.h"
#include "wall_map.h"

#define PI 3.1415926

class SolidObject
{
protected:
	int _user;		//玩家	
	ACL_Color _color;
	int _center[2];	//以画布左上角为原点，SolidObject的中心坐标 -x  |y
	int _angle;		//水平向右为正,顺时针自加
	int _half_length;	//图片长度的1/2
	int _half_width;		//图片宽度的1/2		方便绘图时可以直接根据center对称来绘制
	int _linear_v;
	int _angular_v;

	void _assign_center(int* center1, const int* center2);
	void _for_move(int* new_center);
	void _back_move(int* new_center);
	POINT _point_coordinates();
	void _points_symmetric(POINT* points);
	int _judge_crash();

public:
	SolidObject();
	SolidObject(int user, ACL_Color color, int center0, int center1, int angle, int half_length, int half_width, int linear_v, int angular_v);
	~SolidObject();

	int get_angle();
	POINT* get_points();

	void move_for_per_time();
	void move_back_per_time();
	void rotate_CW_per_time();
	void rotate_CCW_per_time();
};

#endif
