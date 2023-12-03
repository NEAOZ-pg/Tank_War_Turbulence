#ifndef __WALL_MAP_H__
#define __WALL_MAP_H__

#include <Windows.h>
#include "acllib.h"

#define UNIT_LENGTH 120
#define UNIT_LINE 8

class WallMap
{
private:
	int _axis_x;
	int _axis_y;
	int _length;
	int _width;
	int*** wallmap;

private:
	int* _get_frontier(int line, int column);
	void _wallmap_showoneblank(int line, int column);
	void _wallmap_showframe();

public:
	WallMap();
	WallMap(int length, int width, int*** map);
	WallMap(const WallMap& w);
	WallMap &operator=(const WallMap& map1);
	~WallMap();

	int get_axis_x();
	int get_axis_y();
	int get_length();
	int get_width();

	void wallmap_show();

};

#endif
