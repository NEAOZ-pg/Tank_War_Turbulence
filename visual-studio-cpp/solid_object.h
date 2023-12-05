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
	void _points_symmetric(POINT* points);
	int _judge_crash(int* new_center);

public:
	SolidObject();
	SolidObject(int user, ACL_Color color, int center0, int center1, int angle, int half_length, int half_width, int speed);
	~SolidObject();

	int get_angle();
	POINT* get_points();

	void move_for_per_time();
	void move_back_per_time();
	void rotate_CW_per_time();
	void rotate_CCW_per_time();
};

#endif
