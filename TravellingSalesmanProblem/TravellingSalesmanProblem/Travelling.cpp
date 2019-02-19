#include "stdafx.h"
#include "Travelling.h"


Travelling::Travelling()
{
}


Travelling::~Travelling()
{
}


int Travelling::restrain(vector<vector<int>> &matrix)
{
	int wage = 0;
	int currentEdge = 0;
	bool allNoEdge;
	int matrixSize = matrix.size();
	
	//行规约
	for (int i = 0; i < matrixSize; i++)
	{
		allNoEdge = true;

		//从当前行找出最小边权值，进行规约
		int minEdge = matrix[i][0];
		for (int j = 1; j < matrixSize; j++)
		{
			currentEdge = matrix[i][j];
			if (currentEdge != NO_EDGE)
			{
				allNoEdge = false;
				if (minEdge > currentEdge)
					minEdge = currentEdge;
			}
		}

		//如果当前行无边或最小边值为0则不进行计算
		if (allNoEdge == false && minEdge != 0)
		{
			for (int j = 0; j < matrixSize; j++)
			{
				currentEdge = matrix[i][j];
				
				//无边项不变
				if (currentEdge != NO_EDGE)
					matrix.at(i).at(j) -= minEdge;

			}
			wage += minEdge;
		}
	}

	//列规约
	for (int i = 0; i < matrixSize; i++)
	{
		allNoEdge = true;

		//从当前列找出最小边权值，进行规约
		int minEdge = matrix[0][i];
		for (int j = 1; j < matrixSize; j++)
		{
			currentEdge = matrix[j][i];
			if (currentEdge != NO_EDGE)
			{
				allNoEdge = false;
				if (minEdge > currentEdge)
					minEdge = currentEdge;
			}
		}

		//如果当前列无边或最小边值为0则不进行计算
		if (allNoEdge == false && minEdge != 0)
		{
			for (int j = 0; j < matrixSize; j++)
			{
				currentEdge = matrix[j][i];

				//无边项不变
				if (currentEdge != NO_EDGE)
					matrix.at(j).at(i) -= minEdge;

			}
			wage += minEdge;
		}
	}
	return wage;
}


void Travelling::setMatrix()
{
	int matrixSize = size;
	path.reserve(matrixSize - 1);

	//cout << "请输入对应的邻接矩阵：" << endl;
	srand((unsigned int)time(NULL));

	for (int i = 0; i < matrixSize; i++)
	{
		vector<int> col;
		for (int j = 0; j < matrixSize; j++)
		{
			int num;

			//cin >> num;
			num = rand() % 100 + 1;   //+1防止生成0

			col.push_back(num);
		}
		matrix.push_back(col);
	}
	for (int i = 0; i < matrixSize; i++)
		matrix[i][i] = NO_EDGE;

	//cout << "您输入的邻接矩阵为：" << endl;
	cout << "随机生成的邻接矩阵为：" << endl;

	cout << "------------------------------------------------------" << endl;
	for (int i = 0; i < matrixSize; i++)
	{
		for (int j = 0; j < matrixSize; j++)
		{
			cout << matrix[i][j] << "\t";
		}
		cout << endl;
	}
	cout << "------------------------------------------------------" << endl;
	for (int i = 0; i < matrixSize; i++)
	{
		if (matrix[0][i] != NO_EDGE)
			upperBound += matrix[0][i];
	}
	upperBound += matrix[matrixSize - 1][0];
}


void Travelling::findPath()
{
	setMatrix();
	vector<vector<int>> tempMatrix = matrix;
	int tempNode = restrain(tempMatrix);
	Node* firstNode = new Node(tempMatrix, path, tempNode, 0, 0);
	priority_queue<Node*, vector<Node*>, cmp>queue;
	queue.push(firstNode);
	Node* node = NULL;
	int matrixSize = matrix.size();
	cout << "选择过程：" << endl;

	//当优先队列顶端点已经到达叶子节点即找到哈密顿回路时停止搜索
	while (!queue.empty() && queue.top()->level < matrixSize - 1)
	{
		node = queue.top();
		queue.pop();
		path = node->currentPath;
		printPath();
		int j;
		for (int i = 1; i < matrixSize; i++)
		{
			//判断待搜索点是否已经在路径中
			int pathSize = node->currentPath.size();
			for (j = 0; j < pathSize; j++)
				if (i == node->currentPath[j])
					break;
			if (j < pathSize)
				continue;

			tempMatrix = node->matrix;
			int tempWage = node->wage + tempMatrix[node->currentNode][i];
			
			//当前行和被选列置为无穷
			int n = tempMatrix.size();
			for (int k = 0; k < n; k++)
			{
				tempMatrix.at(node->currentNode).at(k) = NO_EDGE;
				tempMatrix.at(k).at(i) = NO_EDGE;
			}

			//重新规约
			tempWage += restrain(tempMatrix);

			//如果下界于上界，入队
			if (tempWage <= upperBound)
			{
				vector<int> tempPath = node->currentPath;
				tempPath.push_back(i);
				Node* newNode = new Node(tempMatrix, tempPath, tempWage, node->level + 1, i);
				queue.push(newNode);
			}

			if (!queue.empty() && queue.top()->level == matrixSize - 1)
			{
				path = queue.top()->currentPath;
				int sum = matrix[0][path.at(0)];
				int n = path.size();
				for (int i = 1; i < n; i++)
					sum += matrix[path.at(i - 1)][path.at(i)];
				sum += matrix[path.at(n - 1)][0];
				if (sum < upperBound)
					upperBound = sum;
			}
		}
	}
	cout << endl << "代价最小的回路为：" << endl;
	printPath();
	printWage();
	matrix.clear();
	path.clear();
}


void Travelling::printPath()
{
	cout << "1 -> ";
	for (int i = 0; i < path.size(); i++)
		cout << path[i] + 1 << " -> ";
	cout << "1" << endl;
}


void Travelling::printWage()
{
	int n = path.size();
	int sum = matrix[0][path.at(0)];
	for (int i = 1; i < n; i++)
		sum += matrix[path.at(i - 1)][path.at(i)];
	sum += matrix[path.at(n - 1)][0];

	cout << "代价权值：\tW = " << sum << endl;
}
