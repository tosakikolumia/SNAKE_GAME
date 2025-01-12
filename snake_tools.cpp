#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include "snake.h"
#include "cmd_console_tools.h"
using namespace std;
void set_map_size(class SNAKE& snake){
	string set[] = { "defalut","set map size" ,"" };
	for (int i = 0; set[i] != ""; i++) {
		cout << i + 1 << ". " << set[i] << endl;
	}
	cout << "input your choice number:";
	while (true) {
		int choice_num = 0;
		cin >> choice_num;
		if (choice_num < 1 || choice_num > 3) {
			continue;
		}
		if (choice_num == 1) {
			return;
		}
		if (choice_num == 2) {
			cout << "input map size(width height):";
			int width = 0, height = 0;
			cin >> width >> height;
			if (width < 1 || height < 1) {
				cout<<"invalid input, please input again"<<endl;
				continue;
			}
			else {
				snake.map_width = width;
				snake.map_height = height;
				return;
			}
		}
	}
}
int menu(class SNAKE& snake) {
	string choice[] = { "Play", "Exit", ""};
	
	for (int i = 0; choice[i]!= ""; i++) {
		cout << i + 1 << ". " << choice[i] << endl;
	}
	cout << "input your choice number:";
	while (true) {
		int choice_num = 0;
		cin >> choice_num;
		if (choice_num < 1 || choice_num > 2) {
			continue;
		}
		if (choice_num == 1) {
			cct_cls();
			set_map_size(snake);
			return 1;
			break;
		}
		if (choice_num == 2) {
			cct_cls();
			return 0;
			break;
		}
	}
}