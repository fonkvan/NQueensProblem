#include "SolveNQueens.h"
#include <cmath>
#include <iostream>

SolveNQueens::SolveNQueens()
{
	N = 1;
	filled = -1;
}

SolveNQueens::SolveNQueens(int N)
{
	this->N = N;
	filled = -1;
}

void SolveNQueens::Solver(std::stack<Position> Queens)
{
	bool bSolved = false;
	while (!bSolved)
	{
		if (Queens.empty())
		{
			Position FirstQueen = Position();
			Queens.push(FirstQueen);
			filled = 0;
		}
		if (!AreConflicts(Queens))
		{
			++filled;
			if (filled == N)
			{
				PrintBoard(N, Queens);
				bSolved = true;
			}
			int StartingRow = Queens.top().row + 1;
			Position NextQueen = Position();
			Queens.push(NextQueen);
			Queens.top().row = StartingRow;
		}
		else
		{
			Queens.top().col += 1;
			while (Queens.top().col >= N)
			{
				--filled;
				Queens.pop();
				if (Queens.empty())
				{
					std::cout << "There are no solutions to this size board." << std::endl;
					return;
				}
				Queens.top().col += 1;
			}
		}
	}
	return;
}

bool SolveNQueens::AreConflicts(std::stack<Position> Queens)
{
	std::stack<Position> Temp = Queens;
	Position current = Temp.top();
	Temp.pop();
	if (Temp.empty())
	{
		return false;
	}
	Position lower = Temp.top();
	if (current.col == lower.col || current.row == lower.row)
	{
		return true;
	}
	while (!Temp.empty())
	{
		lower = Temp.top();
		if (current.col == lower.col)
		{
			return true;
		}
		if (std::abs(current.col - lower.col) == (current.row - lower.row))
		{
			return true;
		}
		Temp.pop();
	}
	return false;
}

void SolveNQueens::PrintBoard(int N, std::stack<Position> Queens)
{
	std::stack<Position> Temp = Queens;
	for (int i = N; i > 0; --i)
	{
		for (int j = N; j > 0; --j)
		{
			Position top = Queens.top();
			if (top.row == i - 1 && top.col == j - 1)
			{
				std::cout << "1 ";
			}
			else
			{
				std::cout << "0 ";
			}
		}
		Queens.pop();
		std::cout << std::endl;
	}
	for (int i = 0; i < N; ++i)
	{
		std::cout << "row: " << Temp.top().row << "     col: " << Temp.top().col << std::endl;
		Temp.pop();
	}
}
