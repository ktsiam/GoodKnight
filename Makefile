
CXX      = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra #-Weverything
LDLFLAGS = -pthread -lpthread

all: chess


chess: basic.o main.o move.o board.o board_gen.o
	${CXX} ${LDFLAGS} -o	chess	basic.o main.o move.o board.o board_gen.o

clean:
	rm -f *.o
	rm -f chess

