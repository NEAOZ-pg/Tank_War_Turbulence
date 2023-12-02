#include <Windows.h>
#include "solid_object.h"

#include "acllib.h"

SolidObject::SolidObject(int user, int center[], int angle, int half_length, int half_width, int speed) :
	_user(user), _angle(angle), _half_length(half_length), _half_width(half_width), _speed(speed)
{
	_center[0] = center[0];
	_center[1] = center[1];
}

SolidObject::~SolidObject()
{
}

/**
  * @brief  ÅÐ¶ÏSolidObjectÊÇ·ñcrash Map
  * @param  None
  * @retval 1:uncrash	0:crash
  */
int SolidObject::edge_judge()
{
	return 0;
}

int SolidObject::move_per_time()
{
	return 0;
}

int SolidObject::rotate_per_time()
{
	return 0;
}
