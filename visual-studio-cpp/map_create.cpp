#include <stdlib.h>

/*
	借助并查集，自动生成连通的地图
*/

/*
以下注释的代码为自动生成地图前的手动生成方式

int*** testmap;

//按照 {UP DOWN LEFT RIGHT}顺序存储
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
*/

/**
  * @brief  为新地图分配空间
  * @param1	length：地图长度		
  * @param2	width：地图宽度
  * @retval 新分配的空间
  */
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

/**
  * @brief  free为新地图分配空间
  * @param1	newmap: 新地图的地址
	@param2	length：地图长度		
	@param3	width：地图宽度
  * @retval	None
  */
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

/**
  * @brief  为地图上的每一个坐标创建一个独一无二的值，主要为了并查集的操作（可逆的hash，其实不能算hash吧）
  * @param1	x
	@param2	y
  * @retval	hash值
  */
int map_hash(int x, int y)
{
	return 100 * x + y;
}

/**
  * @brief  随机生成新地图长宽
  * @param1	*length：地图长度		[3,10]
  * @param2	*width：地图宽度		[2,5]
  * @retval None
  */
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

/**
  * @brief  随机删除地图的一面墙
  * @param1	*x_pos: 删除的墙壁基于的x坐标
  * @param2	*y_pos：删除的墙壁基于的y坐标
  *	@param3	*orient：删除的墙壁基于的x，y坐标的方向
  *	@param4	*x_nxt: 删除的墙壁相邻的x坐标
  *	@param5	*y_nxt：删除的墙壁相邻的y坐标
  * @param6	*length：地图长度
  * @param7	*width：地图宽度
  * @retval	None
  */
void map_random_delete(int*** map, int* x_pos, int* y_pos, int* orient, int* x_nxt, int* y_nxt, int length, int width)
{
	do
	{
		*x_pos = rand() % width;
		*y_pos = rand() % length;
		*orient = rand() % 4;
	} while ((*x_pos == 0 && *orient == 0) || (*x_pos == width - 1 && *orient == 1) ||
		(*y_pos == 0 && *orient == 2) || (*y_pos == length - 1 && *orient == 3) || map[*x_pos][*y_pos][*orient] == 0);

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

/**
  * @brief	并查集基本操作，懒得解释
  * @param1	
  * @retval 
  */
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

/**
  * @brief	并查集基本操作，懒得解释
  * @param1
  * @retval
  */
void fa_free(int* fa)
{
	delete[] fa;
}

/**
  * @brief	并查集基本操作，懒得解释
  * @param1
  * @retval
  */
int fa_find(int* fa, int x)
{
	if (x == fa[x])
		return x;
	else
		return fa[x] = fa_find(fa, fa[x]);
}

/**
  * @brief	检查是否地图是否连通
  * @param1	fa：并查集
  * @param2	*length：地图长度
  * @param3	*width：地图宽度
  * @retval	1：未连通		2：连通
  */
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

/**
  * @brief	生成新的地图
  * @param1	*length：即将随机的地图长度
  * @param2	*width：即将随机的地图宽度
  * @retval	生成的地图指针
  */
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