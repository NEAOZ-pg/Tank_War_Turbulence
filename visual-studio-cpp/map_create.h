#ifndef __MAP_CREATE_H__
#define __MAP_CREATE_H__


//extern int*** testmap;
//void map_read(int length, int width);

void map_free(int*** newmap, int length, int width);
int*** map_creating(int* length, int* width);

#endif
