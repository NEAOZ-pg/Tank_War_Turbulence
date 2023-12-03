#ifndef __SOLID_OBJECT_H__
#define __SOLID_OBJECT_H__

#include <Windows.h>

#include "acllib.h"
#include "wall_map.h"

class SolidObject
{
protected:
	int _user;		//玩家	
	ACL_Color _color;
	int _center[2];	//以画布左上角为原点，SolidObject的中心坐标 -x  |y
	int _angle;		//水平向右为正,顺时针自加
	int _half_length;	//图片长度的1/2
	int _half_width;		//图片宽度的1/2		方便绘图时可以直接根据center对称来绘制
	int _speed;

	POINT _point_coordinates();
	void _points_symmetric(POINT* points, POINT point);
	
public:
	SolidObject(int user, ACL_Color color, int center[], int angle, int half_length, int half_width, int speed);
	~SolidObject();


	//int judge_edge(int* new_center,WallMap my_map);

	void move_for_per_time();
	void move_back_per_time();
	void rotate_CW_per_time();
	void rotate_CCW_per_time();
};

#endif
