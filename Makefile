
CXX      = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra #-O3 #-Weverything
LDLFLAGS = 

all:   chess

chess: main.o
	${CXX} ${LDFLAGS} -o	chess \
basic.o move.o board.o board_gen.o test_board.o main.o 

basic.o:      basic.h basic.cpp
move.o:       move.h move.cpp basic.o
board.o:      board.h board.cpp move.o
board_gen.o:  board_gen.cpp board.o
test_board.o: test_board.cpp board_gen.o
main.o:       main.cpp test_board.o

clean:
	rm -f *.o
	rm -f chess
	rm -rf *.dSYM
	rm -f callgrind*


