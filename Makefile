#Author: Kostas Tsiampouris, Aug-2017

CXX      = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra #-Weverything
LDLFLAGS = -pthread -lpthread

all: checkers


checkers: main.o
	${CXX} ${LDFLAGS} -o	chess	main.o


clean:
	rm -f *.o
	rm -f chess

