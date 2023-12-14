#include <iostream>
#include "acllib.h"

int key_A = 0;
int key_W = 0;
int key_S = 0;
int key_D = 0;
int key_UP = 0;
int key_DOWN = 0;
int key_LEFT = 0;
int key_RIGHT = 0;
int key_ENTER = 0;
int key_SPACE = 0;

int Key_User1_ENABLE = 1;
int Key_User2_ENABLE = 1;

void keyevent(int key, int event)
{
	if (event == KEY_DOWN)
	{
		if (Key_User1_ENABLE)
		{
			if (key == 0x41) { std::cout << "A = 1\n"; key_A = 1; }
			else if (key == 0x57) { std::cout << "W = 1\n"; key_W = 1; }
			else if (key == 0x53) { std::cout << "S = 1\n"; key_S = 1; }
			else if (key == 0x44) { std::cout << "D = 1\n"; key_D = 1; }
			else if (key == 0x20) { std::cout << "SPACE = 1\n"; key_SPACE = 1; }
		}
		if (Key_User2_ENABLE)
		{
			if (key == 0x25) { std::cout << "LEFT = 1\n"; key_LEFT = 1; }
			else if (key == 0x26) { std::cout << "UP = 1\n"; key_UP = 1; }
			else if (key == 0x27) { std::cout << "RIGHT = 1\n"; key_RIGHT = 1; }
			else if (key == 0x28) { std::cout << "DOWN = 1\n"; key_DOWN = 1; }
			else if (key == 0x0D) { std::cout << "ENTER = 1\n"; key_ENTER = 1; }
		}
	}
	else if (event == KEY_UP)
	{
		if (key == 0x41) { std::cout << "A = 0\n"; key_A = 0; }
		else if (key == 0x57) { std::cout << "W = 0\n"; key_W = 0; }
		else if (key == 0x53) { std::cout << "S = 0\n"; key_S = 0; }
		else if (key == 0x44) { std::cout << "D = 0\n"; key_D = 0; }
		else if (key == 0x0D) { std::cout << "ENTER = 0\n"; key_ENTER = 0; }
		else if (key == 0x20) { std::cout << "SPACE = 0\n"; key_SPACE = 0; }
		else if (key == 0x25) { std::cout << "LEFT = 0\n"; key_LEFT = 0; }
		else if (key == 0x26) { std::cout << "UP = 0\n"; key_UP = 0; }
		else if (key == 0x27) { std::cout << "RIGHT = 0\n"; key_RIGHT = 0; }
		else if (key == 0x28) { std::cout << "DOWN = 0\n"; key_DOWN = 0; }
	}
}