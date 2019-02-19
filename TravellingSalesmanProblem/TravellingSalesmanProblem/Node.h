#pragma once
#include<vector>
using namespace std;

class Node
{
	friend struct cmp;
	friend class Travelling;
public:
	Node();
	Node(vector<vector<int>>matrix, vector<int>currentPath, int wage, int level, int currentNode)
	{
		this->matrix = matrix;
		this->currentPath = currentPath;
		this->wage = wage;
		this->level = level;
		this->currentNode = currentNode;
	}
	~Node();
private:
	//�ڽӾ���
	vector<vector<int>> matrix;
	//��ǰ·��
	vector<int> currentPath;
	//��Լ����ֵ
	int wage;
	//��ǰ�ڵ���������
	int level;
	//��ǰ�ڵ���
	int currentNode;
};


struct cmp
{
	bool operator()(Node* &first, Node* &second)
	{
		return first->wage > second->wage;
	}
};

