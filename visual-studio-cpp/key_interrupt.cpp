#include <iostream>
#include "acllib.h"

#include "global_param.h"

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

int Mouse_MENU_Start = 0;
int Mouse_MENU_INTRODUCTION = 0;
int Mouse_MENU_DEVELPOMENT = 0;
int Mouse_MENU_EXIT = 0;
int Mouse_PAUSE_CONTINUE = 0;
int Mouse_PAUSE_MENU = 0;
int Mouse_PAUSE_EXIT = 0;
int Mouse_PLAY_PAUSE = 0;
int Mouse_MENU_RETURN = 0;

/**
  * @brief  清除user1键盘标志
  * @param  None
  * @retval None
  */
void user1_key_remake()
{
	key_A = 0;
	key_W = 0;
	key_S = 0;
	key_D = 0;
	key_SPACE = 0;
}

/**
  * @brief  清除user2键盘标志
  * @param  None
  * @retval None
  */
void user2_key_remake()
{
	key_UP = 0;
	key_DOWN = 0;
	key_LEFT = 0;
	key_RIGHT = 0;
	key_ENTER = 0;
}

/**
  * @brief  键盘事件判断
  * @param  见ACCLIB
  * @retval 见ACCLIB
  */
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

/**
  * @brief  鼠标事件判断
  * @param  见ACCLIB
  * @retval 见ACCLIB
  */
void mouseevent(int x, int y, int button, int event)
{
	if (button == LEFT_BUTTON)
	{
		if (event == BUTTON_DOWN)
		{
			if (interface_state == INTERFACE_MENU_BEGIN)
			{
				if (x > 520 && x < 800 && y > 430 && y < 510)
				{
					std::cout << "Mouse_MENU_Start\n";
					Mouse_MENU_Start = 1;
				}
				else if (x > 170 && x < 450 && y > 465 && y < 545)
				{
					std::cout << "Mouse_MENU_DEVELPOMENT\n";
					Mouse_MENU_DEVELPOMENT = 1;
				}
				else if (x > 520 && x < 800 && y > 530 && y < 605)
				{
					std::cout << "Mouse_MENU_INTRODUCTION\n";
					Mouse_MENU_INTRODUCTION = 1;
				}
				else if (x > 860 && x < 1140 && y > 465 && y < 545)
				{
					std::cout << "Mouse_MENU_EXIT\n";
					Mouse_MENU_EXIT = 1;
				}
			}
			else if (interface_state == INTERFACE_MENU_PAUSE)
			{
				if (x > 400 && x < 900 && y > 150 && y < 250)
				{
					std::cout << "Mouse_PAUSE_CONTINUE\n";
					Mouse_PAUSE_CONTINUE = 1;
				}
				else if (x > 400 && x < 900 && y > 350 && y < 450)
				{
					std::cout << "Mouse_PAUSE_MENU\n";
					Mouse_PAUSE_MENU = 1;
				}
				else if (x > 400 && x < 900 && y > 550 && y < 650)
				{
					std::cout << "Mouse_PAUSE_EXIT\n";
					Mouse_PAUSE_EXIT = 1;
				}
			}
			else if (interface_state == INTERFACE_GAME_INIT || interface_state == INTERFACE_GAME_PLAY)
			{
				if (x > 1200 && y > 700)
				{
					std::cout << "Mouse_PLAY_PAUSE\n";
					Mouse_PLAY_PAUSE = 1;
				}
			}
			else if (interface_state == INTERFACE_MENU_INTRODUCTION || interface_state == INTERFACE_MENU_DEVELPOER)
			{
				if (x > 1200 && y > 700)
				{
					std::cout << "Mouse_MENU_RETURN\n";
					Mouse_MENU_RETURN = 1;
				}
			}
		}
	}
}