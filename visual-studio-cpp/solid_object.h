#ifndef __SOLID_OBJECT_H__
#define __SOLID_OBJECT_H__

#include <Windows.h>

#include "acllib.h"
#include "wall_map.h"

class SolidObject
{
protected:
	int _user;		//���	
	ACL_Color _color;
	int _center[2];	//�Ի������Ͻ�Ϊԭ�㣬SolidObject���������� -x  |y
	int _angle;		//ˮƽ����Ϊ��,˳ʱ���Լ�
	int _half_length;	//ͼƬ���ȵ�1/2
	int _half_width;		//ͼƬ��ȵ�1/2		�����ͼʱ����ֱ�Ӹ���center�Գ�������
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
