#pragma once
#include <vector>
#include <queue>
using namespace std;
#define MAX_FOOD 3
enum DIRECTION { UP, RIGHT, DOWN, LEFT , NONE };//�ߵķ���
enum OBJECT { EMPTY, SNAKE, FOOD, WALL };//��ͼ�Ķ���
enum RESULT { WIN, LOSE, RUNNING };//��Ϸ�Ľ��
class SNAKE {
protected:
	int bg_color, fg_color;//��ȡ����ɫ������ɫ
	int snake_x, snake_y;//��ͷ������
	queue<pair<int, int>> body;//���������,����ͷ��ʼ���Դ�����
	int direction;//�ߵ�ǰ������0��ʾ���ϣ�1��ʾ���ң�2��ʾ���£�3��ʾ����
	int length;//�ߵĳ���
	int score;//�ߵķ���
	int speed;//�ߵ��ٶ�
	//��ͼ�Ĵ�С
	int map_width, map_height;
	vector<vector<int>> map;//��ͼ
	vector<pair<int,int>>food_map;//ʳ���λ��
public:
	SNAKE();//���캯��,Ĭ�ϵ�ͼ��СΪ10*10
	SNAKE(int w, int h);//���캯��,�Զ����ͼ��С
	void set_direction(DIRECTION d);//�����ߵķ���
	RESULT snake_move();//�ߵ��ƶ�����
	void print_game();//��ӡ��Ϸ��ͼ
	void set_food_map();//���õ�ͼ
	friend void set_map_size(SNAKE& snake);


	void draw_snake();//����
	void draw_wall();//��ǽ
	void print_score();//��ӡ����

	int get_score() const {
		//��ȡ�ߵķ���
		return score;
	}
	int get_width() const {
		//��ȡ��ͼ�Ŀ��
		return map_width;
	}
	int get_height() const {//��ȡ��ͼ�ĸ߶�
		return map_height;
	}
	int get_speed() const {//��ȡ�ߵ��ٶ�
		return speed;
	}
};


void set_map_size(class SNAKE& snake);
int menu(class SNAKE& snake);