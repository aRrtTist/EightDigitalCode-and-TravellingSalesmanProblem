#pragma once
#include<iostream>
using namespace std;
const int N = 3;
const int MAX_STEP = 100;
enum Direction{None, Up,Down, Left,Right};


class Chess
{
	friend Chess * hillClimbingSearch(Chess *begin, Chess *target, int &depth);
	friend Chess * branchBoundSearch(Chess *begin, Chess *target, int &depth);
	friend struct cmp;
public:
	Chess();
	~Chess();
private:
	int cell[N][N];
	int value;
	Direction blockedDirection;
public :
	Chess * parent;
	int evaluate(Chess* target);
	void setChess();
	void printChess();
	Chess* moveChess(Direction direction);
};

