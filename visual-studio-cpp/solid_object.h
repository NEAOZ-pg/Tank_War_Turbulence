#ifndef __SOLID_OBJECT_H__
#define __SOLID_OBJECT_H__

class SolidObject
{
protected:
	int _user;		//���	
	int _center;	//�Ե�ͼ���Ͻ�Ϊԭ�㣬SolidObject����������
	int _angle;		//ˮƽ����Ϊ��
	int _length;	
	int _width;
	int _speed;

	SolidObject(int user, int center, int angle, int length, int width, int speed);

	int edge_judge();

	int move_per_time();

};

#endif
