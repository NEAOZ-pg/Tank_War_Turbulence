#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS

#include "tank.h"

#include <stdlib.h>
#include "global_param.h"

#define TANK_LENGTH		25
#define TANK_WIDTH		15
#define TANK_LINEAR_V	9
#define TANK_ANGULAR_V	15

int tank1_green_score = 0;
int tank2_blue_score = 0;

//INIT

Tank::Tank()
{
}

Tank::Tank(int user, ACL_Color color, int* center, int angle) :
	SolidObject(user, color, center[0], center[1], angle, TANK_LENGTH, TANK_WIDTH, TANK_LINEAR_V, TANK_ANGULAR_V)
{
}

Tank::~Tank()
{
}

//private

/**
  * @brief  ����̹���ڹܵ��ĸ��ǵ�ַ
  * @param  point:���ڴ���ڹ��ĸ���λ��
  * @retval None
  */
POINT* Tank::_points_cannon(POINT* points)
{
	POINT cannon[4];
	cannon[0].x = (points[0].x * 2 + points[3].x) / 3;
	cannon[0].y = (points[0].y * 2 + points[3].y) / 3;
	cannon[1].x = (points[3].x * 2 + points[0].x) / 3;
	cannon[1].y = (points[3].y * 2 + points[0].y) / 3;
	cannon[2].x = _center[0] + (cannon[1].x - cannon[0].x) / 2;
	cannon[2].y = _center[1] + (cannon[1].y - cannon[0].y) / 2;
	cannon[3].x = _center[0] + (cannon[0].x - cannon[1].x) / 2;
	cannon[3].y = _center[1] + (cannon[0].y - cannon[1].y) / 2;
	return cannon;
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
int Tank::_judge_move_crash(int* next_center)
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

int Tank::_judge_rotate_crash(int next_angle)
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

/**
  * @brief  �����һ��̹��λ����ʾ
  * @param  None
  * @retval None
  */
void Tank::tank_unshow()
{
	setPenColor(WHITE);
	setPenWidth(0);
	setBrushColor(WHITE);
	setBrushStyle(BRUSH_STYLE_SOLID);
	//����̹�˻���
	POINT points[4];
	_points_symmetric(points, _center, _angle);
	polygon(points, 4);
	//����̹���ڹܣ���һ�ο��ܲ�������ȫ��
	polygon(_points_cannon(points), 4);
}

/**
  * @brief  ̹��λ����ʾ
  * @param  None
  * @retval None
  */
void Tank::tank_show()
{
	setPenColor(EMPTY);
	setPenWidth(0);
	setBrushColor(_color);
	setBrushStyle(BRUSH_STYLE_SOLID);
	//��ʾ̹�˻���
	POINT points[4];
	_points_symmetric(points, _center, _angle);
	polygon(points, 4);
	//��ʾ̹���ڹܣ�͵���˾Ͷ��Ǻ�ɫ��
	setBrushColor(RED);
	polygon(_points_cannon(points), 4);
}

/**
  * @brief  ��ǰ�ƶ�
  * @param  None
  * @retval None
  */
void Tank::move_for_per_time()
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
void Tank::move_back_per_time()
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
void Tank::rotate_CW_per_time()
{
	_angle += _angular_v;
	//_judge_rotate_crash(_angle + _angular_v);
}

/**
  * @brief  ��ʱ�루counterclockwise����ת
  * @param  None
  * @retval None
  */
void Tank::rotate_CCW_per_time()
{
	_angle -= _angular_v;
	//_judge_rotate_crash(_angle - _angular_v);
}


/**
  * @brief  �������tank��λ��,λ��ÿһ����ͼ�������
  * @param  my_map : wallmap
  * @retval random_center[2]
  */
int* Tank::random_coordinate(WallMap my_map)
{
	int random_c[2];
	do 
	{
		random_c[0] = rand() % (my_map.get_length() - 1) * UNIT_LENGTH + UNIT_LENGTH / 2 + my_map.get_axis_x();
		random_c[1] = rand() % (my_map.get_width() - 1) * UNIT_LENGTH + UNIT_LENGTH / 2 + my_map.get_axis_y();
	}while(getPixel(random_c[0],random_c[1]) != WHITE);

	return random_c;
}

/**
  * @brief  �������angle(0,90,180,270)
  * @param  None
  * @retval angle
  */
int Tank::random_angle()
{
	return rand() % 4 * 90;
}

/**
  * @brief  ��ʾtank����
  * @param  None
  * @retval None
  */
void Tank::show_score()
{
	putImage(&img_Tankblue, 800, 700);
	putImage(&img_Tankgreen, 300, 700);
	
	setTextColor(GREY);
	setTextBkColor(WHITE);
	setTextSize(32);
	setTextFont(font_name);

	//int -> string
	char int_str[10];
	itoa(tank1_green_score, int_str, 10);
	paintText(420, 740, int_str);

	itoa(tank2_blue_score, int_str, 10);
	paintText(760, 740, int_str);
}

/**
  * @brief  ���
  * @param  None
  * @retval None
  */
void Tank::clear_score()
{
	tank1_green_score = 0;
	tank2_blue_score = 0;
}
