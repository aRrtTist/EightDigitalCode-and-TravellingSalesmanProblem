#include "stdafx.h"
#include "Chess.h"


Chess::Chess()
{
	value = 0;
	parent = NULL;
	blockedDirection = None;
}


Chess::~Chess()
{
}


int Chess::evaluate(Chess* target)
{
	int error = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (cell[i][j] != target->cell[i][j] && cell[i][j] != 0)
				error++;
	value = error;
	return error;
}


void Chess::setChess()
{
	cout << "ÇëÊäÈë" << N << " X " << N << "¾ØÕó£º" << endl;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> cell[i][j];
}


void Chess::printChess()
{
	cout << "------------------------------------" << endl;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			cout << cell[i][j] << "\t";
		cout << endl;
	}
	cout << "\t\t\tw(n)= " << value << endl;
	cout << "------------------------------------" << endl;
}


Chess* Chess::moveChess(Direction direction)
{
	Chess *newChess;
	int i, j, t_i, t_j;
	bool hasGetBlankCell = false;
	bool ableMove = true;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
			if (cell[i][j] == 0)
			{
				hasGetBlankCell = true;
				break;
			}
		if (hasGetBlankCell)
			break;
	}
	t_i = i;
	t_j = j;
	switch(direction)
	{
	case Up:
		t_i--;
		if (t_i < 0)
			ableMove = false;
		break;
	case Down:
		t_i++;
		if (t_i > N)
			ableMove = false;
		break;
	case Left:
		t_j--;
		if (t_j < 0)
			ableMove = false;
		break;
	case Right:
		t_j++;
		if (t_j > N)
			ableMove = false;
		break;
	};
	if (!ableMove)
		return this;
	newChess = new Chess();
	for (int x = 0; x < N; x++)
		for (int y = 0; y < N; y++)
			newChess->cell[x][y] = cell[x][y];
	newChess->cell[i][j] = newChess->cell[t_i][t_j];
	newChess->cell[t_i][t_j] = 0;
	return newChess;
}
