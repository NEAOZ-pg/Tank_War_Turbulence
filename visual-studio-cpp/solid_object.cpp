#include "solid_object.h"

#define ANGULAR_V 10

SolidObject::SolidObject()
{
}

SolidObject::SolidObject(int user, ACL_Color color, int center0, int center1,
	int angle, int half_length, int half_width, int speed) :
	_user(user), _color(color), _angle(angle), _half_length(half_length), _half_width(half_width), _speed(speed)
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
	_points_symmetric(points);
	return points;
}

// protected

void SolidObject::_assign_center(int* center1, const int* center2)
{
	center1[0] = center2[0];
	center1[1] = center2[1];
}

void SolidObject::_next_move(int* new_center)
{
	new_center[0] = _center[0] + (int)(_half_length * cos(_angle * PI / 180)
		+ _half_width * cos((_angle + 90) * PI / 180));
	new_center[1] = _center[1] + (int)(_half_length * sin(_angle * PI / 180)
		+ _half_width * sin((_angle + 90) * PI / 180));
}

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
void SolidObject::_points_symmetric(POINT *points)
{
	POINT point = _point_coordinates();
	points[0].x = point.x;
	points[0].y = point.y;
	points[1].x = (long)(point.x - 2 * _half_length * cos(_angle * PI / 180));
	points[1].y = (long)(point.y - 2 * _half_length * sin(_angle * PI / 180));
	points[2].x = 2 * _center[0] - points[0].x;
	points[2].y = 2 * _center[1] - points[0].y;
	points[3].x = 2 * _center[0] - points[1].x;
	points[3].y = 2 * _center[1] - points[1].y;
}


int SolidObject::_judge_crash()
{
	POINT points[4];
	_points_symmetric((points));


	//�жϳ���ײ���ӵ���һ�С�
	/*
	����ʹ�õı�����
	int new_center[2]	//���window���ڣ�����windowinit���������Ĵ������Ͻ�Ϊԭ�㣨0��0��
	int angle, int half_length, int half_width�������ò�����

	��������䣬��õ�points �ṹ�峤����
	typedef struct tagPOINT
	{
		LONG  x;
		LONG  y;
	} POINT,
	���ĸ��ǵ�x��y��
	˳�򣨵�̹�˳����ұߵ�ʱ�򣩣�������ʱ�룺���Ͻǣ����Ͻǣ����½ǣ����½ǡ�

	ACL_Color getPixel(int x, int y);������ԭ����acclib.h��
	������ɫ��ֻҪ���ǰ�ɫ��ʲô��û�У��ͣ�GREY���ӵ��������������߽�
											���ӵ���ʱ�����ǣ�

	����ֵ��0�����Ǳ߽磬1���߽�������ײ����2���߽�������ײ��
					3���߽�������ײ����4���߽�������ײ��
	*/

	return 0;
}

//public

void SolidObject::move_for_per_time()
{
	if (!_judge_crash())
	{
		_center[0] += (int)(cos(_angle * PI / 180) * _speed);
		_center[1] += (int)(sin(_angle * PI / 180) * _speed);
	}
}

void SolidObject::move_back_per_time()
{
	if (!_judge_crash())
	{
		_center[0] -= (int)(cos(_angle * PI / 180) * _speed);
		_center[1] -= (int)(sin(_angle * PI / 180) * _speed);
	}
}

void SolidObject::rotate_CW_per_time()
{
	_angle = (_angle + ANGULAR_V) % 360;
	//�жϣ�
}

void SolidObject::rotate_CCW_per_time()
{
	_angle = (_angle - ANGULAR_V) % 360;
	//�жϣ�
}

/**
  * @brief  �ж�SolidObject�Ƿ�crash Map
  * @param  None
  * @retval 1:uncrash	0:crash
  */
