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
  * @brief  �����ҷ��Ͻǵĵ㣨_angle = 0)������
  * @param  None
  * @retval �ڻ�������ϵ�µ����꣨x��y��
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
  * @brief  �����ҷ��Ͻǵĵ���������Ľ�����
  * @param  �ҷ��Ͻǵĵ�����
  * @retval	points[4]{x,y} �ڻ�������ϵ�µ��Ľ�����
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
	//�жϱ߽�
	
	����ʹ�õı�����
	int new_center[2]	//��������Ŵ�ͼ����280 * 210�����Ͻ�Ϊԭ�㣨0��0��
	int angle, int half_length, int half_width

	my_map.pixel_check(int x, int y) == white ��Ϊ�����ؿ鲻�Ǳ߽磨�ǰ�ɫ�������������ӵ�����̹�ˣ�
																��ʱ�����ǣ��������ֻ�Ա߽��жϣ�
	�����жϱ߽��ĳ�����Ƿ��Ǳ߽������

	����ֵ��0�����Ǳ߽磬1���߽�������ײ����2���߽�������ײ��
					3���߽�������ײ����4���߽�������ײ��

	

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
	//�жϣ�
}

/**
  * @brief  �ж�SolidObject�Ƿ�crash Map
  * @param  None
  * @retval 1:uncrash	0:crash
  */
