
CXX      = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra #-O3 #-Weverything
LDLFLAGS = 

chess: main.o
	${CXX} ${LDFLAGS} -o	chess	basic.o main.o move.o board.o board_gen.o test_board.o

basic.o:      basic.h basic.cpp
move.o:       move.h move.cpp basic.o
board.o:      board.h move.o
board_gen.o:  board.o
test_board.o: board_gen.o
main.o:       test_board.o

clean:
	rm -f *.o
	rm -f chess
	rm -rf *.dSYM
	rm -f callgrind*

