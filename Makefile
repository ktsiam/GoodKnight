
CXX      = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra #-O3
LDLFLAGS = -lpthread

all:   chess

chess: main.o
	${CXX} ${LDFLAGS} -o	chess \
basic.o move.o board.o move_maker.o move_generator.o test_board.o main.o 

basic.o:            basic.h basic.cpp
move.o:             move.h move.cpp basic.o
board.o:            board.h board.cpp move.o
move_generator.o:   move_generator.cpp board.o
move_maker.o:       move_maker.cpp board.o
test_board.o:       test_board.cpp move_maker.o move_generator.o
main.o:             main.cpp test_board.o

clean:
	rm -f *.o
	rm -f chess
	rm -rf *.dSYM
	rm -f callgrind*


