#ifndef __WALL_MAP_H__
#define __WALL_MAP_H__

#include <Windows.h>
#include "acllib.h"

#define WINDOW_LENGTH 1300
#define WINDOW_WIDTH 800

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

public:
	WallMap();
	WallMap(int length, int width, int*** map);
	WallMap(const WallMap& w);
	WallMap& operator=(const WallMap& map1);
	~WallMap();

private:
	void _wallmap_showoneblock(int line, int column);
	void _wallmap_showframe();

public:
	int get_axis_x();
	int get_axis_y();
	int get_length();
	int get_width();

	void wallmap_show();

	static void windows_clear();
};

#endif
