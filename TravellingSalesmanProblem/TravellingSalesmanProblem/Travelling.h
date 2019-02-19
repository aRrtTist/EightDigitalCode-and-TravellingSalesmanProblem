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
	//�ڽӾ����С
	int size;
	//�ڽӾ���
	vector<vector<int>> matrix;
	//��С����·��
	vector<int> path;
	//�Ͻ�
	int upperBound;
public:
	void findPath();
private:
	//�����ڽӾ��󣬷��ع�Լ����ֵ
	int restrain(vector<vector<int>> &matrix);
	void setMatrix();
	void printPath();
	void printWage();
};

