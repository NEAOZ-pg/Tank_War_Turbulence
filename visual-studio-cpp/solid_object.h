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
	int _user;					//��ң���ţ�
	ACL_Color _color;			//��ɫ
	int _center[2];				//�Ի������Ͻ�Ϊԭ�㣬SolidObject���������� -x  |y
	int _angle;					//ˮƽ����Ϊ��,˳ʱ���Լ�
	int _half_length;			//���ȵ�1/2
	int _half_width;			//��ȵ�1/2		�����ͼʱ����ֱ�Ӹ���center�Գ�������
	int _linear_v;				//���ٶ�
	int _angular_v;				//���ٶ�

public:
	SolidObject();
	SolidObject(int user, ACL_Color color, int center0, int center1, int angle, int half_length, int half_width, int linear_v, int angular_v);
	~SolidObject();

protected:
	void _assign_center(int* center1, const int* center2);
	void _for_move(int* new_center);
	void _back_move(int* new_center);
	POINT _point_coordinates(int* center, int angle);
	void _points_symmetric(POINT* points, int* center, int angle);
	int _judge_move_crash(int *next_center);
	int _judge_rotate_crash(int next_angle);

public:
	int get_angle();
	void get_points(POINT* points);

	void move_for_per_time();
	void move_back_per_time();
	void rotate_CW_per_time();
	void rotate_CCW_per_time();
};

#endif
