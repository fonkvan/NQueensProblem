#include "Position.h"
#include "SolveNQueens.h"
#include <iostream>
#include <stack>

int main()
{
	SolveNQueens Solve;
	std::stack<Position> Queens;
	int N;
	std::cout << "How many Queens would you like to solve for?" << std::endl;
	std::cin >> N;
	Solve = SolveNQueens(N);
	Solve.Solver(Queens);
	return 0;
}
