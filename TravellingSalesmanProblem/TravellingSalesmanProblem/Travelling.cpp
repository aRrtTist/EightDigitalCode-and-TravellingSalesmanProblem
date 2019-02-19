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
	
	//�й�Լ
	for (int i = 0; i < matrixSize; i++)
	{
		allNoEdge = true;

		//�ӵ�ǰ���ҳ���С��Ȩֵ�����й�Լ
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

		//�����ǰ���ޱ߻���С��ֵΪ0�򲻽��м���
		if (allNoEdge == false && minEdge != 0)
		{
			for (int j = 0; j < matrixSize; j++)
			{
				currentEdge = matrix[i][j];
				
				//�ޱ����
				if (currentEdge != NO_EDGE)
					matrix.at(i).at(j) -= minEdge;

			}
			wage += minEdge;
		}
	}

	//�й�Լ
	for (int i = 0; i < matrixSize; i++)
	{
		allNoEdge = true;

		//�ӵ�ǰ���ҳ���С��Ȩֵ�����й�Լ
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

		//�����ǰ���ޱ߻���С��ֵΪ0�򲻽��м���
		if (allNoEdge == false && minEdge != 0)
		{
			for (int j = 0; j < matrixSize; j++)
			{
				currentEdge = matrix[j][i];

				//�ޱ����
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

	//cout << "�������Ӧ���ڽӾ���" << endl;
	srand((unsigned int)time(NULL));

	for (int i = 0; i < matrixSize; i++)
	{
		vector<int> col;
		for (int j = 0; j < matrixSize; j++)
		{
			int num;

			//cin >> num;
			num = rand() % 100 + 1;   //+1��ֹ����0

			col.push_back(num);
		}
		matrix.push_back(col);
	}
	for (int i = 0; i < matrixSize; i++)
		matrix[i][i] = NO_EDGE;

	//cout << "��������ڽӾ���Ϊ��" << endl;
	cout << "������ɵ��ڽӾ���Ϊ��" << endl;

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
	cout << "ѡ����̣�" << endl;

	//�����ȶ��ж��˵��Ѿ�����Ҷ�ӽڵ㼴�ҵ����ܶٻ�·ʱֹͣ����
	while (!queue.empty() && queue.top()->level < matrixSize - 1)
	{
		node = queue.top();
		queue.pop();
		path = node->currentPath;
		printPath();
		int j;
		for (int i = 1; i < matrixSize; i++)
		{
			//�жϴ��������Ƿ��Ѿ���·����
			int pathSize = node->currentPath.size();
			for (j = 0; j < pathSize; j++)
				if (i == node->currentPath[j])
					break;
			if (j < pathSize)
				continue;

			tempMatrix = node->matrix;
			int tempWage = node->wage + tempMatrix[node->currentNode][i];
			
			//��ǰ�кͱ�ѡ����Ϊ����
			int n = tempMatrix.size();
			for (int k = 0; k < n; k++)
			{
				tempMatrix.at(node->currentNode).at(k) = NO_EDGE;
				tempMatrix.at(k).at(i) = NO_EDGE;
			}

			//���¹�Լ
			tempWage += restrain(tempMatrix);

			//����½����Ͻ磬���
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
	cout << endl << "������С�Ļ�·Ϊ��" << endl;
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

	cout << "����Ȩֵ��\tW = " << sum << endl;
}
