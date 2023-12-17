#include "solid_object.h"

//INIT

SolidObject::SolidObject()
{
	_user = -1;	
	_color = EMPTY;
	_center[0] = 0;
	_center[1] = 0;
	_angle = 0;
	_half_length = 0;
	_half_width = 0;
	_linear_v = 0;
	_angular_v = 0;
}

SolidObject::SolidObject(int user, ACL_Color color, int center0, int center1,
	int angle, int half_length, int half_width, int linear_v, int angular_v) :
	_user(user), _color(color), _angle(angle), _half_length(half_length), 
	_half_width(half_width), _linear_v(linear_v), _angular_v(angular_v)
{
	_center[0] = center0;
	_center[1] = center1;
}

SolidObject::~SolidObject()
{
}

// protected

/**
  * @brief  ��center2��ֵ��center1
  * @param1	center1������
  * @param2	center2������
  * @retval None
  */
void SolidObject::_assign_center(int* center1, const int* center2)
{
	center1[0] = center2[0];
	center1[1] = center2[1];
}

/**
  * @brief  ���������ǰ�ƶ�_center
  * @param1	new_center:��������ƶ����ֵ
  * @retval None
  */
void SolidObject::_for_move(int* new_center)
{
	new_center[0] = _center[0] + round((cos(_angle * PI / 180) * _linear_v));
	new_center[1] = _center[1] + round((sin(_angle * PI / 180) * _linear_v));
}

/**
  * @brief  �����������ƶ�_center
  * @param1	new_center:��������ƶ����ֵ
  * @retval None
  */
void SolidObject::_back_move(int* new_center)
{
	new_center[0] = _center[0] - round((cos(_angle * PI / 180) * _linear_v));
	new_center[1] = _center[1] - round((sin(_angle * PI / 180) * _linear_v));
}

/**
  * @brief  �����ҷ��Ͻǵĵ㣨���_angle = 0)������
  * @param  None
  * @retval �ڻ�������ϵ�µ����꣨x��y��
  */
POINT SolidObject::_point_coordinates(int* center, int angle)
{
	POINT coordiante =
	{
		center[0] + (long)round(_half_length * cos(angle * PI / 180) 
			+ _half_width * cos((angle + 90) * PI / 180)),
		center[1] + (long)round(_half_length * sin(angle * PI / 180)
			+ _half_width * sin((angle + 90) * PI / 180)),
	};
	return coordiante;
}

/**
  * @brief  �����ҷ��Ͻǵĵ���������Ľ�����
  * @param  �ҷ��Ͻǵĵ�����
  * @retval	points[4]{x,y} �ڻ�������ϵ�µ��Ľ�����
  */ 
void SolidObject::_points_symmetric(POINT *points, int *center, int angle)
{
	POINT point = _point_coordinates(center, angle);
	points[0].x = point.x;
	points[0].y = point.y;
	points[1].x = (long)round(point.x - 2 * _half_length * cos(angle * PI / 180));
	points[1].y = (long)round(point.y - 2 * _half_length * sin(angle * PI / 180));
	points[2].x = 2 * center[0] - points[0].x;
	points[2].y = 2 * center[1] - points[0].y;
	points[3].x = 2 * center[0] - points[1].x;
	points[3].y = 2 * center[1] - points[1].y;
}

//public

int SolidObject::get_angle()
{
	return _angle;
}

/**
  * @brief  ��ȡ�Ľǵ�����
  * @param  None
  * @retval None
  */
void SolidObject::get_points(POINT* points)
{
	_points_symmetric(points, _center, _angle);
}

