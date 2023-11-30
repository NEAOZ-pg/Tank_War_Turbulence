#include "solid_object.h"

SolidObject::SolidObject(int user, int center, int angle, int length, int width, int speed) :
	_user(user), _center(center), _angle(angle), _length(length), _width(width) ,_speed(speed)
{}

/**
  * @brief  ÅÐ¶ÏSolidObjectÊÇ·ñcrash Map
  * @param  None
  * @retval 1:uncrash	0:crash
  */
int SolidObject::edge_judge()
{
	return 0;
}
