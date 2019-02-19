// TravellingSalesmanProblem.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Travelling.h"


int main()
{
	int size;
	cout << "\t***************************************" << endl;
	cout << "\t     基于分支界限法的旅行推销商问题    " << endl;
	cout << "\t***************************************" << endl;
	cout << "请输入城市数量：" << endl;
	cin >> size;
	Travelling travel(size);
	travel.findPath();
	return 0;
}

