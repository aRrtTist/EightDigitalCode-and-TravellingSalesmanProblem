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
	//邻接矩阵
	vector<vector<int>> matrix;
	//当前路径
	vector<int> currentPath;
	//规约代价值
	int wage;
	//当前节点所处层数
	int level;
	//当前节点编号
	int currentNode;
};


struct cmp
{
	bool operator()(Node* &first, Node* &second)
	{
		return first->wage > second->wage;
	}
};

