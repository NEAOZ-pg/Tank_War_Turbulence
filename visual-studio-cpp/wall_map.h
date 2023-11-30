#ifndef __WALL_MAP_H__
#define __WALL_MAP_H__

#include <Windows.h>

#define UNIT_LENGTH 70
#define UNIT_LINE 5

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
	WallMap(int length, int width, int*** map);
	WallMap(const WallMap& w);
	~WallMap();

	int get_axis_x();
	int get_axis_y();

	int get_length();
	int get_width();

	int* get_rela_quare_nine_center(int* center);
	int** get_square_nine(int* center);
	void free_square_nine(int** nine_map);

	void wallmap_show();

};

#endif
