#ifndef __SOLID_OBJECT_H__
#define __SOLID_OBJECT_H__

#include <Windows.h>

#include "acllib.h"
#include "wall_map.h"

class SolidObject
{
protected:
	int _user;		//���	
	int _center[2];	//�Ե�ͼ���Ͻ�Ϊԭ�㣬SolidObject���������� -x  |y
	int _angle;		//ˮƽ����Ϊ��
	int _half_length;	//ͼƬ���ȵ�1/2
	int _half_width;		//ͼƬ��ȵ�1/2		�����ͼʱ����ֱ�Ӹ���center�Գ�������
	int _speed;

public:
	SolidObject(int user, int center[], int angle, int half_length, int half_width, int speed);
	~SolidObject();


	int edge_judge();

	int move_per_time();
	int rotate_per_time();

};

#endif
