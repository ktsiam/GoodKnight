
CXX      = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O3
LDLFLAGS = 

all:   chess

chess: main.o
	${CXX} ${LDFLAGS} -o	chess  basic.o move.o board.o move_maker.o \
	move_generator.o evaluator.o traverser.o interface.o main.o 

basic.o:                     basic.h          basic.cpp
move.o:                       move.h 	       move.cpp                  basic.o
board.o:           state.h   board.h          board.cpp                   move.o
move_maker.o:           move_maker.h     move_maker.cpp                  board.o
move_generator.o:   move_generator.h move_generator.cpp                  board.o
evaluator.o:             evaluator.h      evaluator.cpp         move_generator.o
traverser.o:             traverser.h      traverser.cpp move_maker.o evaluator.o
interface.o:           	 interface.h      interface.cpp              traverser.o
main.o:                                        main.cpp              interface.o

clean:
	rm -f  chess
	rm -f  *.o
	rm -f  callgrind*
	rm -rf *.dSYM


