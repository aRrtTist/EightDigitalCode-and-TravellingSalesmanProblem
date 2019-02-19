#pragma once
#include<iostream>
using namespace std;
const int N = 3;
//最大搜索次数
const int MAX_STEP = 50;
//空格移动方向
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
	//评估值
	int value;
	//屏蔽方向
	Direction blockedDirection;
public:
	Chess * parent;
public:
	int evaluate(Chess* target);
	void setChess();
	void printChess();
	Chess * moveChess(Direction direction);
};

