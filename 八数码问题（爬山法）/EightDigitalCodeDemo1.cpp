// EightDigitalCodeDemo1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Chess.h"
#include<queue>
#include<stack>


//迭代器
struct cmp
{
	bool operator()(Chess *a, Chess *b)
	{
		return a->value > b->value;
	}
};

//爬山法搜索函数
Chess * hillClimbingSearch(Chess* begin, Chess* target, int &depth)
{
	Chess *p1, *p2, *p=NULL;
	//搜索深度
	depth = 0;
	priority_queue<Chess *, vector<Chess *>,cmp>queue;
	queue.push(begin);
	while (p == NULL || queue.empty())
	{
		//利用优先队列选取权值最小节点展开
		p1 = queue.top();
		while(!queue.empty())
			queue.pop();
		for (int i = 1; i <= 4; i++)
		{
			Direction direction = (Direction)i;

			//跳过屏蔽方向
			if (direction == p1->blockedDirection)
				continue;

			p2 = p1->moveChess(direction);
			if (p2 != p1)
			{
				p2->evaluate(target);
				if (p2->value <= p1->value)
				{
					p2->parent = p1;
					switch (direction)
					{
					case Up:
						p2->blockedDirection = Down;
						break;
					case Down:
						p2->blockedDirection = Up;
						break;
					case Left:
						p2->blockedDirection = Right;
						break;
					case Right:
						p2->blockedDirection = Left;
						break;
					}
					queue.push(p2);

					//搜索完成，结束循环
					if (p2->value == 0)
					{
						p = p2;
						i = 5;
					}

				}
				else
				{
					delete p2;
					p2 = NULL;
				}
			}
		}
		depth++;

		//搜索次数超过最大搜索次数
		if (depth > MAX_STEP)
			return NULL;

	}
	return p;
}

int main()
{
	int depth;
	Chess *begin, *target, *t;
	begin = new Chess();
	target = new Chess();
	cout << "*******************************" << endl;
	cout << "    八数码问题——爬山法版本" << endl;
	cout << "*******************************" << endl;
	cout << "请设置目标棋盘：" << endl;
	target->setChess();
	cout << "请设置初始棋盘：" << endl;
	begin->setChess();
	begin->evaluate(target);
	t = hillClimbingSearch(begin, target,depth);
	if (t)
	{
		Chess *p = t;
		stack<Chess *>stack;
		while (p->parent != NULL)
		{
			stack.push(p);
			p = p->parent;
		}
		cout << "搜索结果：" << endl;
		while (!stack.empty())
		{
			stack.top()->printChess();
			stack.pop();
		}
		cout << "搜索完成！" << endl;
		cout << "移动次数为：" << depth << "次" << endl;
	}
	else
		cout << "搜索不到结果，搜索深度为：" << depth;
	delete begin, target;
    return 0;
}

