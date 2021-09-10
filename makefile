CC = g++
CFLAGS = -g -Wall

Position.o: Position.h Position.cpp
	$(CC) $(CFLAGS) -c Position.cpp

SolveNQueens.o: SolveNQueens.h SolveNQueens.cpp
	$(CC) $(CFLAGS) -c SolveNQueens.cpp

main.o: main.cpp SolveNQueens.h Position.h
	$(CC) $(CFLAGS) -c main.cpp

Solution: main.o SolveNQueens.o Position.o
	$(CC) $(CFLAGS) main.o SolveNQueens.o Position.o -o Solution

gdb:
	gdb Solution

clean:
	rm -f *.o
	rm Solution

run:
	./Solution
