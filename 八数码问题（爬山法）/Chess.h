#pragma once
#include<iostream>
using namespace std;
const int N = 3;
//�����������
const int MAX_STEP = 50;
//�ո��ƶ�����
enum Direction{None, Up, Down, Left, Right};


class Chess
{
	friend Chess * hillClimbingSearch(Chess* begin, Chess* target, int &depth);
	friend struct cmp;
public:
	Chess();
	~Chess();
private:
	int cell[N][N];
	//����ֵ
	int value;
	//���η���
	Direction blockedDirection;
public:
	Chess * parent;
public:
	int evaluate(Chess* target);
	void setChess();
	void printChess();
	Chess * moveChess(Direction direction);
};

