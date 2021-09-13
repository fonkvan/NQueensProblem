#include "SolveNQueens.h"
#include <cmath>
#include <iostream>

//Basic Constructor
SolveNQueens::SolveNQueens()
{
	N = 1;
	filled = -1;
}

//Constuctor that specifies the number of Queens N and size of board NxN
SolveNQueens::SolveNQueens(int N)
{
	this->N = N;
	filled = -1;
}

//This is the main function. The idea is to pass the stack of queens
//Then while the problem has not been solved, we loop. If the stack is empty, that means there is no queens in there
//So we need to push an inital queen onto the stack
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
		//Next we check for conflicts. If there are no conflicts, add 1 to filled.
		//if filled is the size of N, we're finished and we can print the board and set bSolved to true
		//otherwise we're going to add a new queen to the stack, with the starting row being the next row from the current queen.
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
		//Otherwise, meaning there are conflicts, then we move the queen over one column. Then, we do a while loop and check if
		// the column number is greater than or equal to N. We loop here because we want to remove each and every Queen that "overflows"	
		//we take 1 off filled, and pop the top queen. If popping the top queen makes the board empty, that means we have checked
		//all solutions, and therefore there is no possible solution for this N.
		//If it's not empty, we add 1 to the top column
		//we add 1 to top column to insure that we are checking a NEW location for the queen. If we did not check it
		//then we would get the same result we did last time at this queen (no conflicts) and we would get stuck in a loop between this queen
		//and the next.
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

//To check for conflicts, we're going to pass in our stack, and then create a copy of it.
//We create a copy, because in order to check the stack, which we can only see the top item,
//we need to pop off the top item to go deeper. Therefore, we need to make sure we don't interfere with our true stack.
bool SolveNQueens::AreConflicts(std::stack<Position> Queens)
{
	std::stack<Position> Temp = Queens;
	Position current = Temp.top();
	//pop top off as we're going to be comparing the original item, to the items below
	Temp.pop();
	//There can be no conflicts if the stack is empty.
	if (Temp.empty())
	{
		return false;
	}
	Position lower;
	while (!Temp.empty())
	{
		//This is where I check the diagonals but also the straight lines
		//we only need to check the column and not he row here, as when we're going deeper, we're already guaranteeing that we
		//are higher than the one lower since we use row +=1 earlier when adding to the stack, so we only need check column
		//we check lines again since we're in a loop and continually going lower and lower
		lower = Temp.top();
		if (current.col == lower.col)
		{
			return true;
		}
		//if you draw a chess board and look at it a diagonal, you will see that a diagonal is always 1 space or more
		//up or down, and 1 space left or right
		//This means the difference between the two pieces columns, and the difference between their rows will be the same (if on same diagonal)
		//higher piece always has higher row, so this isn't going to be negative
		//lower piece could have higher column though, so we need to check the absolute value
		if (std::abs(current.col - lower.col) == (current.row - lower.row))
		{
			return true;
		}
		//if we get through all of that without any conflicts, we need to pop the top of temp and check the next lower queen.
		Temp.pop();
	}
	return false;
}

//Goes through and prints the board, since the stack goes from 'top' to bottom, we start from N and work way down. 1 for queen, 0 for empty space
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
}
