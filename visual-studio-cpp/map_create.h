#ifndef __MAP_CREATE_H__
#define __MAP_CREATE_H__

extern int*** testmap;

void map_read(int length, int width);

int*** map_new(int length, int width);
void map_free(int*** newmap, int length, int width);
int map_hash(int x, int y);
int* fa_new(int length, int width);
void fa_free(int* fa);
int fa_find(int* fa, int x);
void map_random_length_width(int* length, int* width);
void map_random_delete(int*** map, int* x_pos, int* y_pos, int* orient, int* x_nxt, int* y_nxt, int length, int width);
bool map_check(int* fa, int length, int width);
int*** map_creating(int* length, int* width);

#endif
