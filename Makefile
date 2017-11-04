#Author: Kostas Tsiampouris, Aug-2017

CXX      = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra #-Weverything
LDLFLAGS = -pthread -lpthread

all: checkers


checkers: main.o files_ranks.o board.o basic.o #move.o
	${CXX} ${LDFLAGS} -o	chess	main.o files_ranks.o board.o basic.o #move.o

clean:
	rm -f *.o
	rm -f chess

