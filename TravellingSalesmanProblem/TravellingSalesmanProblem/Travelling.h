#pragma once
#include<iostream>
using namespace std;
#include "Node.h"
#include<queue>
#include<stack>
#include <stdlib.h>
#include<time.h>

#define NO_EDGE  65535

class Travelling
{
public:
	Travelling();
	Travelling(int size)
	{
		this->size = size;
		this->upperBound = 0;
	}
	~Travelling();
private:
	//邻接矩阵大小
	int size;
	//邻接矩阵
	vector<vector<int>> matrix;
	//最小代价路径
	vector<int> path;
	//上界
	int upperBound;
public:
	void findPath();
private:
	//输入邻接矩阵，返回规约代价值
	int restrain(vector<vector<int>> &matrix);
	void setMatrix();
	void printPath();
	void printWage();
};

