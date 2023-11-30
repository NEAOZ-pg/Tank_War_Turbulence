#ifndef __SOLID_OBJECT_H__
#define __SOLID_OBJECT_H__

#include <Windows.h>

#include "acllib.h"
#include "wall_map.h"

class SolidObject
{
protected:
	int _user;		//玩家	
	int _center[2];	//以地图左上角为原点，SolidObject的中心坐标 -x  |y
	int _angle;		//水平向右为正
	int _half_length;	//图片长度的1/2
	int _half_width;		//图片宽度的1/2		方便绘图时可以直接根据center对称来绘制
	int _speed;

public:
	SolidObject(int user, int center[], int angle, int half_length, int half_width, int speed);
	~SolidObject();


	int edge_judge();

	int move_per_time();
	int rotate_per_time();

};

#endif
