
CXX      = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra #-O3 #-Weverything
LDLFLAGS = 

all: chess


chess: basic.o main.o move.o board.o board_gen.o board_print.o
	${CXX} ${LDFLAGS} -o	chess	basic.o main.o move.o board.o board_gen.o board_print.o

clean:
	rm -f *.o
	rm -f chess
	rm -rf *.dSYM

