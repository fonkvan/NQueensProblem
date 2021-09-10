#pragma once
#include "Position.h"
#include <stack>
class SolveNQueens
{
	public:
		SolveNQueens();
		SolveNQueens(int N);
		void Solver(std::stack<Position> Queens);
		void PrintBoard(int N, std::stack<Position> Queens);
		bool AreConflicts(std::stack<Position> Queens);
	private:
		int filled;
		int N;
};

