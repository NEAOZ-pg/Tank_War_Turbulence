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

/*
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
	

	return 0;
}*/
int SolidObject::_judge_move_crash(int* next_center)
{
	ACL_Color target;
	POINT origin_points[4];
	_points_symmetric(origin_points, _center, _angle);
	int process_center[2];//ѭ��������������
	POINT process_point[4];//ѭ�������ĸ���
	POINT next_points[4];
	_points_symmetric(next_points, next_center, _angle);
	int i, j;//����ѭ��
	float coefficient;
	int slope;//б��
	int sign;//����
	if (next_center[0] >= _center[0])
		sign = 1;
	else sign = -1;
	if (next_center[0] != _center[0])
	{
		coefficient = (next_center[1] - _center[1]) / (next_center[0] - _center[0]);
		if (next_center[0] > _center[0])
			slope = 1;
		else slope = -1;
	}
	else {
		slope = 0;
		if (next_center[1] > _center[1])
			coefficient = 1;
		else coefficient = -1;
	}//ȷ��б��
	process_center[0] = _center[0];
	process_center[1] = _center[1];
	for (j = 0; j < 4; ++j)
	{
		process_point[j].x = origin_points[j].x;
		process_point[j].y = origin_points[j].y;
	}//�Ȱѹ��̱�����С����ʼ״̬����
	for (i = 0; i <= abs(next_center[0] - _center[0]); ++i)
	{
		process_center[0] = process_center[0] + slope;
		process_center[1] = process_center[1] + sign * (int)(coefficient);
		for (j = 0; j < 4; ++j)
		{
			process_point[j].x = process_point[j].x + slope;
			process_point[j].y = process_point[j].y + sign * (int)(coefficient);
			target = getPixel(process_point[j].x, process_point[j].y);
			if ((target == BLACK) || (target == BLUE) || (target == GREEN))
			{
				_center[0] = process_center[0] - slope;
				_center[1] = process_center[1] - sign * (int)(coefficient);
				return 1;
			}
		}
	}
	_center[0] = next_center[0];
	_center[1] = next_center[1];//��;û��ײǽ���ƶ�����������λ��
	return 0;
}

int SolidObject::_judge_rotate_crash(int next_angle)
{
	//_angular_v=next_angle-_angle;
	//�������ֻģ����תһ��ʮ�ȵ����
	//_angle,_center,origin_points��֪
	ACL_Color target;
	POINT origin_points[4];
	_points_symmetric(origin_points, _center, _angle);
	POINT process_points[5];//����ȡ���ж�
	POINT judge_points[5];//�����жϱߵ�����
	POINT next_points[4];
	_points_symmetric(next_points, _center, next_angle);
	int sign[4];//ȡ�㷽��
	int coefficient[4], slope[4];//y����ı�����x����ı�����
	int i, j;//ѭ�����Ʊ���
	for (i = 0; i < 5; ++i)
	{
		if (i == 4)
		{
			judge_points[i].x = next_points[0].x;
			judge_points[i].y = next_points[0].y;
			break;
		}
		judge_points[i].x = next_points[i].x;
		judge_points[i].y = next_points[i].y;
	}
	//
	for (i = 0; i < 4; ++i)
	{
		if (judge_points[i + 1].x >= judge_points[i].x)
			sign[i] = 1;
		else sign[i] = -1;
		if (next_points[i].x != next_points[i + 1].x)
		{
			coefficient[i] = (next_points[i + 1].y - next_points[i].y) / (next_points[i + 1].x - next_points[i].x);
			if (next_points[i + 1].x > next_points[i].x)
				slope[i] = 1;
			else slope[i] = -1;
		}
		else {
			slope[i] = 0;
			if (next_points[i + 1].y > next_points[i].y)
				coefficient[i] = 1;
			else coefficient[i] = -1;
		}//ȷ��б��
	}

	for (j = 0; j < 5; ++j)
	{
		process_points[j].x = judge_points[j].x;
		process_points[j].y = judge_points[j].y;
	}//�Ȱѹ��̱�����С����ʼ״̬����

	for (i = 0; i <= 4; ++i)
	{
		for (j = 0; j <= abs(process_points[i + 1].x - process_points[i].x); ++j)
		{
			process_points[i].x = process_points[i].x + slope[i];
			process_points[i].y = process_points[i].y + sign[i] * (int)(coefficient[i]);
			target = getPixel(process_points[i].x, process_points[i].y);
			if ((target == BLACK) || (target == BLUE) || (target == GREEN))
				return 1;
		}
	}
	_angle = next_angle;
	return 0;
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

/**
  * @brief  ��ǰ�ƶ�
  * @param  None
  * @retval None
  */
void SolidObject::move_for_per_time()
{
	//_for_move(_center);

	int next_center[2];
	_for_move(next_center);
	_judge_move_crash(next_center);
}

/**
  * @brief  ����ƶ�
  * @param  None
  * @retval None
  */
void SolidObject::move_back_per_time()
{
	//_back_move(_center);

	int next_center[2];
	_back_move(next_center);
	_judge_move_crash(next_center);
}

/**
  * @brief  ˳ʱ�루clockwise����ת
  * @param  None
  * @retval None
  */
void SolidObject::rotate_CW_per_time()
{
	_angle += _angular_v;
	//_judge_rotate_crash(_angle + _angular_v);
}

/**
  * @brief  ��ʱ�루counterclockwise����ת
  * @param  None
  * @retval None
  */
void SolidObject::rotate_CCW_per_time()
{
	_angle -= _angular_v;
	//_judge_rotate_crash(_angle - _angular_v);
}

