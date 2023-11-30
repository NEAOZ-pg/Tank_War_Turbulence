#ifndef __WALL_MAP_H__
#define __WALL_MAP_H__

class WallMap
{
private:
	int _axis_x;
	int _axis_y;
	int _length;
	int _width;
	int*** wallmap;

private:
	void wallmap_showoneblank(int line, int column);
	void wallmap_showframe();
public:

	WallMap(int length, int width, int*** map);
	~WallMap();

	int* get_frontier(int line, int column);

	void wallmap_show();

};

#endif
