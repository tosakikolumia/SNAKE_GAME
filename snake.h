#pragma once
#include <vector>
#include <queue>
using namespace std;
#define MAX_FOOD 3
enum DIRECTION { UP, RIGHT, DOWN, LEFT , NONE };//蛇的方向
enum OBJECT { EMPTY, SNAKE, FOOD, WALL };//地图的对象
enum RESULT { WIN, LOSE, RUNNING };//游戏的结果
class SNAKE {
protected:
	int bg_color, fg_color;//获取背景色和字体色
	int snake_x, snake_y;//蛇头的坐标
	queue<pair<int, int>> body;//蛇身的坐标,从蛇头开始，以此类推
	int direction;//蛇的前进方向，0表示向上，1表示向右，2表示向下，3表示向左
	int length;//蛇的长度
	int score;//蛇的分数
	int speed;//蛇的速度
	//地图的大小
	int map_width, map_height;
	vector<vector<int>> map;//地图
	vector<pair<int,int>>food_map;//食物的位置
public:
	SNAKE();//构造函数,默认地图大小为10*10
	SNAKE(int w, int h);//构造函数,自定义地图大小
	void set_direction(DIRECTION d);//设置蛇的方向
	RESULT snake_move();//蛇的移动函数
	void print_game();//打印游戏地图
	void set_food_map();//设置地图
	friend void set_map_size(SNAKE& snake);


	void draw_snake();//画蛇
	void draw_wall();//画墙
	void print_score();//打印分数

	int get_score() const {
		//获取蛇的分数
		return score;
	}
	int get_width() const {
		//获取地图的宽度
		return map_width;
	}
	int get_height() const {//获取地图的高度
		return map_height;
	}
	int get_speed() const {//获取蛇的速度
		return speed;
	}
};


void set_map_size(class SNAKE& snake);
int menu(class SNAKE& snake);