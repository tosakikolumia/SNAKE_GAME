#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include "cmd_console_tools.h"
#include "snake.h"
using namespace std;
SNAKE::SNAKE() {
	map_width = 50;
	map_height = 25;
	snake_x = map_width / 2;
	snake_y = map_height / 2;
	direction = DIRECTION::RIGHT;
	length = 3;
	score = 0;
	map.resize(map_height, vector<int>(map_width, 0));//初始化地图
	for (int i = 0; i < map_width; i++) {
		for (int j = 0; j < map_height; j++) {
			if (i == 0 || i == map_width - 1 || j == 0 || j == map_height - 1) {//边界
				map[j][i] = OBJECT::WALL;
			}
			else if (i == snake_x && j == snake_y) {
				map[j][i] = OBJECT::SNAKE;//蛇头
				map[j][i - 1] = OBJECT::SNAKE;
				map[j][i - 2] = OBJECT::SNAKE;
				body.push(make_pair(i - 2, j));
				body.push(make_pair(i - 1, j));
				body.push(make_pair(snake_x, snake_y));
			}
			else {
				map[j][i] = OBJECT::EMPTY;//空地
			}
		}
	}
	speed = 500;
	cct_getcolor(bg_color, fg_color);
}
SNAKE::SNAKE(int x, int y) {//地图大小
	map_width = x;
	map_height = y;
	snake_x = map_width / 2;
	snake_y = map_height / 2;
	direction = DIRECTION::RIGHT;
	length = 3;
	score = 0;
	map.resize(map_height, vector<int>(map_width, 0));//初始化地图
	for (int i = 0; i < map_width; i++) {
		for (int j = 0; j < map_height; j++) {
			if (i == 0 || i == map_width - 1 || j == 0 || j == map_height - 1) {//边界
				map[j][i] = OBJECT::WALL;
			}
			if (i == snake_x && j == snake_y) {
				map[j][i] = OBJECT::SNAKE;//蛇头
				
				map[j][i - 1] = OBJECT::SNAKE;
				
				map[j][i - 2] = OBJECT::SNAKE;
				body.push(make_pair(i - 2, j));
				body.push(make_pair(i - 1, y));
				body.push(make_pair(snake_x, snake_y));
			}
		}
	}
	speed = 500;
	cct_getcolor(bg_color, fg_color);
}
void SNAKE::set_direction(DIRECTION d) {
	switch (d) {
		case DIRECTION::UP:
			if (direction != DIRECTION::DOWN) {
				direction = d;
			}
			break;
		case DIRECTION::DOWN:
			if (direction != DIRECTION::UP) {
				direction = d;
			}
			break;
		case DIRECTION::LEFT:
			if (direction != DIRECTION::RIGHT) {
				direction = d;
			}
			break;
		case DIRECTION::RIGHT:
			if (direction != DIRECTION::LEFT) {
				direction = d;
			}
			break;
		defalut:
			direction = direction;
			break;
	}
	
}
RESULT SNAKE::snake_move() {
	switch (direction) {
		case DIRECTION::UP:
			snake_y--;
			break;
		case DIRECTION::DOWN:
			snake_y++;
			break;
		case DIRECTION::LEFT:
			snake_x--;
			break;
		case DIRECTION::RIGHT:
			snake_x++;
			break;
		default:
			break;
	}
	if (snake_x < 0 || snake_x >= map_width || snake_y < 0 || snake_y >= map_height) {//越界
		return RESULT::LOSE;
	}
	if (map[snake_y][snake_x] == OBJECT::WALL) {//撞墙
		return RESULT::LOSE;
	}
	if (map[snake_y][snake_x] == OBJECT::SNAKE) {//撞自己
		return RESULT::LOSE;
	}
	if (map[snake_y][snake_x] == OBJECT::FOOD) {//吃苹果
		score++;
		length++;
		map[snake_y][snake_x] = OBJECT::SNAKE;
		food_map.erase(find(food_map.begin(), food_map.end(), make_pair(snake_x, snake_y)));//删除苹果
		body.push(make_pair(snake_x, snake_y));
		//更新图像
		cct_showstr(snake_x * 2, snake_y, "  ", COLOR_HYELLOW, COLOR_HYELLOW);
	}
	else {
		map[snake_y][snake_x] = OBJECT::SNAKE;
		body.push(make_pair(snake_x, snake_y));
		map[body.front().second][body.front().first] = OBJECT::EMPTY;
		//更新图像
		cct_showstr(snake_x * 2, snake_y, "  ", COLOR_HYELLOW, COLOR_HYELLOW);
		cct_showstr(body.front().first * 2, body.front().second, "  ", bg_color, fg_color);

		body.pop();
	}
	return RESULT::RUNNING;
}
void SNAKE::print_game() {
	for (int i = 0; i < map_height; i++) {
		for (int j = 0; j < map_width; j++) {
			switch (map[i][j]) {
				case OBJECT::EMPTY:
					cout << " ";
					break;
				case OBJECT::WALL:
					cout << "#";
					break;
				case OBJECT::SNAKE:
					cout << "O";
					break;
				case OBJECT::FOOD:
					cout << "*";
					break;
				default:
					break;
			}
		}
		cout << endl;
	}
	cout << "Score: " << score << endl;
}
void SNAKE::set_food_map() {
	srand(static_cast<unsigned int>(time(0)));
	int x, y;
	while (food_map.size() < MAX_FOOD) {
		x = rand() % map_width;
		y = rand() % map_height;
		if (map[y][x] == OBJECT::EMPTY) {
			food_map.push_back(make_pair(x, y));
		}
		map[food_map.back().second][food_map.back().first] = OBJECT::FOOD;
		cct_showstr(food_map.back().first * 2, food_map.back().second, "  ", COLOR_PINK, COLOR_PINK);
	}
}
void SNAKE::draw_wall() {
	for (int i = 0; i < map_height; i++) {
		for (int j = 0; j < map_width; j++) {
			if(map[i][j] == OBJECT::WALL)
				cct_showstr(j*2, i, "  ", COLOR_WHITE, COLOR_WHITE);
		}
	}
}
void SNAKE::draw_snake() {
	for (int i = 0; i < map_height; i++) {
		for (int j = 0; j < map_width; j++) {
			if(map[i][j] == OBJECT::SNAKE)
				cct_showstr(j*2, i, "  ", COLOR_HYELLOW, COLOR_HYELLOW);
		}
	}
}
void SNAKE::print_score() {
	cct_showstr(0, map_height + 1, "score: ", COLOR_BLACK, COLOR_WHITE);
	cout<<score<<endl;
	cct_setcolor();
}