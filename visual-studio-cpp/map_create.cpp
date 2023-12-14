#include <stdlib.h>

int*** testmap;

//UP DOWN LEFT RIGHT
int map1[3][3][4] = {
	{{1,1,1,0},{1,0,0,1},{1,0,1,1},},
	{{1,0,1,1},{0,1,1,0},{0,0,0,1},},
	{{0,1,1,0},{1,1,0,0},{0,1,0,1},},
};

int map2[3][4][4] = {
	{{1,1,1,0},{1,0,0,1},{1,0,1,0},{1,1,0,1},},
	{{1,0,1,1},{0,1,1,0},{0,0,0,1},{1,0,1,1},},
	{{0,1,1,0},{1,1,0,0},{0,1,0,0},{0,1,0,1},},
};

void map_read(int length, int width)
{
	testmap = new int** [width];
	int line = 0, column = 0, i = 0;
	for (line = 0; line < width; line++)
	{
		testmap[line] = new int* [length];
		for (column = 0; column < length; column++)
		{
			testmap[line][column] = new int[4];
			for (i = 0; i < 4; i++)
			{
				testmap[line][column][i] = map2[line][column][i];
			}
		}
	}
}

int*** map_new(int length, int width)
{
	int*** newmap = new int** [width];
	int line = 0, column = 0, i = 0;
	for (line = 0; line < width; line++)
	{
		newmap[line] = new int* [length];
		for (column = 0; column < length; column++)
		{
			newmap[line][column] = new int[4];
			for (i = 0; i < 4; i++)
			{
				newmap[line][column][i] = 1;
			}
		}
	}
	return newmap;
}

void map_free(int*** newmap, int length, int width)
{
	int line = 0, column = 0;
	for (line = 0; line < width; line++)
	{
		for (column = 0; column < length; column++)
		{
			delete[] newmap[line][column];
		}
		delete[] newmap[line];
	}
	delete[] newmap;
}

int map_hash(int x, int y)
{
	return 100 * x + y;
}

void map_random_length_width(int* length, int* width)
{
	*length = rand() % 8 + 3;
	*width = rand() % 4 + 2;
	if (*length < *width)
	{
		int swap = *length;
		*width = *length;
		*length = swap;
	}
}

void map_random_delete(int*** map, int* x_pos, int* y_pos, int* orient, int* x_nxt, int* y_nxt, int length, int width)
{
	do
	{
		*x_pos = rand() % width;
		*y_pos = rand() % length;
		*orient = rand() % 4;
	} while ((*x_pos == 0 && *orient == 0) || (*x_pos == width - 1 && *orient == 1) ||
		(*y_pos == 0 && *orient == 2) || (*y_pos == length - 1 && *orient == 3) || map[*x_pos][*y_pos][*orient] == 0);
	
	//while (map[*x_pos][*y_pos][*orient] == 0)
	//{
	//	if (*orient % 2)
	//	{
	//		if (++*x_pos == width)
	//		{
	//			*x_pos = 0;
	//			*y_pos = (*y_pos + 2) % length;
	//		}
	//	}
	//	else
	//	{
	//		if (++*y_pos == length)
	//		{
	//			*y_pos = 0;
	//			*x_pos = (*x_pos + 2) % width;
	//		}
	//	}
	//}
	
	*x_nxt = *x_pos;
	*y_nxt = *y_pos;
	int nxt_orient = 0;
	if (*orient == 0)
	{
		*x_nxt = *x_pos - 1;
		nxt_orient = 1;
	}
	else if (*orient == 1)
	{
		*x_nxt = *x_pos + 1;
		nxt_orient = 0;
	}
	else if (*orient == 2)
	{
		*y_nxt = *y_pos - 1;
		nxt_orient = 3;
	}
	else if (*orient == 3)
	{
		*y_nxt = *y_pos + 1;
		nxt_orient = 2;
	}
	map[*x_pos][*y_pos][*orient] = 0;
	map[*x_nxt][*y_nxt][nxt_orient] = 0;
}

int* fa_new(int length, int width)
{
	int fa_len = map_hash(width, length);
	int* fa = new int[fa_len];
	int i = 0;
	for (i = 0; i < fa_len; i++)
	{
		fa[i] = i;
	}
	return fa;
}

void fa_free(int* fa)
{
	delete[] fa;
}

int fa_find(int* fa, int x)
{
	if (x == fa[x])
		return x;
	else
		return fa[x] = fa_find(fa, fa[x]);
}

bool map_check(int* fa, int length, int width)
{
	int ancestor = fa_find(fa, 0);
	int line = 0, column = 0;
	for (line = 0; line < width; ++line)
		for (column = 0; column < length; ++column)
			if (ancestor != fa_find(fa, map_hash(line, column)))
				return 1;
	return 0;
}

int*** map_creating(int *length, int *width)
{
	map_random_length_width(length, width);
	int*** newmap = map_new(*length, *width);
	int* fa = fa_new(*length, *width);

	int x_pos = 0, y_pos = 0, orient;
	int x_nxt = 0, y_nxt = 0;
	do
	{
		map_random_delete(newmap, &x_pos, &y_pos, &orient, &x_nxt, &y_nxt, *length, *width);
		fa[fa_find(fa, map_hash(x_pos, y_pos))] = fa_find(fa, map_hash(x_nxt, y_nxt));
	} while (map_check(fa, *length, *width));

	fa_free(fa);
	return newmap;
}