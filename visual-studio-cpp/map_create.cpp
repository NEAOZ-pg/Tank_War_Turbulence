#include <stdlib.h>

/*
	�������鼯���Զ�������ͨ�ĵ�ͼ
*/

/*
����ע�͵Ĵ���Ϊ�Զ����ɵ�ͼǰ���ֶ����ɷ�ʽ

int*** testmap;

//���� {UP DOWN LEFT RIGHT}˳��洢
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
  * @brief  Ϊ�µ�ͼ����ռ�
  * @param1	length����ͼ����		
  * @param2	width����ͼ���
  * @retval �·���Ŀռ�
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
  * @brief  freeΪ�µ�ͼ����ռ�
  * @param1	newmap: �µ�ͼ�ĵ�ַ
	@param2	length����ͼ����		
	@param3	width����ͼ���
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
  * @brief  Ϊ��ͼ�ϵ�ÿһ�����괴��һ����һ�޶���ֵ����ҪΪ�˲��鼯�Ĳ����������hash����ʵ������hash�ɣ�
  * @param1	x
	@param2	y
  * @retval	hashֵ
  */
int map_hash(int x, int y)
{
	return 100 * x + y;
}

/**
  * @brief  ��������µ�ͼ����
  * @param1	*length����ͼ����		[3,10]
  * @param2	*width����ͼ���		[2,5]
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
  * @brief  ���ɾ����ͼ��һ��ǽ
  * @param1	*x_pos: ɾ����ǽ�ڻ��ڵ�x����
  * @param2	*y_pos��ɾ����ǽ�ڻ��ڵ�y����
  *	@param3	*orient��ɾ����ǽ�ڻ��ڵ�x��y����ķ���
  *	@param4	*x_nxt: ɾ����ǽ�����ڵ�x����
  *	@param5	*y_nxt��ɾ����ǽ�����ڵ�y����
  * @param6	*length����ͼ����
  * @param7	*width����ͼ���
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
  * @brief	���鼯�������������ý���
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
  * @brief	���鼯�������������ý���
  * @param1
  * @retval
  */
void fa_free(int* fa)
{
	delete[] fa;
}

/**
  * @brief	���鼯�������������ý���
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
  * @brief	����Ƿ��ͼ�Ƿ���ͨ
  * @param1	fa�����鼯
  * @param2	*length����ͼ����
  * @param3	*width����ͼ���
  * @retval	1��δ��ͨ		2����ͨ
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
  * @brief	�����µĵ�ͼ
  * @param1	*length����������ĵ�ͼ����
  * @param2	*width����������ĵ�ͼ���
  * @retval	���ɵĵ�ͼָ��
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