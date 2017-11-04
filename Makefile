#Author: Kostas Tsiampouris, Aug-2017

CXX      = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra #-Weverything
LDLFLAGS = -pthread -lpthread

all: checkers


checkers: basic.o main.o board.o move.o
	${CXX} ${LDFLAGS} -o	chess	basic.o main.o board.o move.o

clean:
	rm -f *.o
	rm -f chess

