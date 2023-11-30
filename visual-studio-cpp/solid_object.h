#ifndef __SOLID_OBJECT_H__
#define __SOLID_OBJECT_H__

class SolidObject
{
protected:
	int _user;		//玩家	
	int _center;	//以地图左上角为原点，SolidObject的中心坐标
	int _angle;		//水平向右为正
	int _length;	
	int _width;
	int _speed;

	SolidObject(int user, int center, int angle, int length, int width, int speed);

	int edge_judge();

	int move_per_time();

};

#endif
