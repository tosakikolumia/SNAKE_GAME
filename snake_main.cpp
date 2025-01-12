#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <windows.h>
#include <conio.h>
#include "cmd_console_tools.h"
#include "snake.h"
using namespace std;
DIRECTION get_keyboard() {
	if (_kbhit()) {
		int MX, MY, MAction;
		int key1, key2;
		int ret = cct_read_keyboard_and_mouse(MX, MY, MAction, key1, key2);
		if (ret == CCT_KEYBOARD_EVENT) {
			switch (key1) {
				case 0xE0:
					switch (key2) {
						case KB_ARROW_UP:
							return DIRECTION::UP;
						case KB_ARROW_DOWN:
							return DIRECTION::DOWN;
						case KB_ARROW_LEFT:
							return DIRECTION::LEFT;
						case KB_ARROW_RIGHT:
							return DIRECTION::RIGHT;
						default:
							return DIRECTION::NONE;
					}
				default:
					return DIRECTION::NONE;
			}
		}
	}
	return DIRECTION::NONE;
}
int main() {
	class SNAKE snake;
	if (menu(snake) == 0) {//游戏结束
		return 0;
    }
   cct_setconsoleborder(2 * snake.get_width(), 2 * snake.get_height());//设置窗口边框
   cct_cls();//清屏
   snake.draw_wall();
   snake.draw_snake();
   cct_setcolor();
   cct_enable_mouse();
   while(1){
	   Sleep(snake.get_speed());
	   snake.set_food_map();
	   snake.print_score();
	   //cct_cls();//清屏
	   DIRECTION direction = get_keyboard();
	   if(direction!= DIRECTION::NONE){
		   snake.set_direction(direction);
	   }
	   RESULT result = snake.snake_move();
	   

	   cct_setcolor();
	   if (result == RESULT::LOSE) {
		   cct_cls();//清屏
		   cct_gotoxy(snake.get_width() / 2, snake.get_height() / 2);
		   cout << "Game Over!" << endl;
		   return 0;
	   }
	   else if(result == RESULT::RUNNING) {
		   continue;
	   }
   }
}