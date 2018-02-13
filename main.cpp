#include <iostream>

#include "interface.h"

unsigned TIME_TAKEN;
unsigned MOVE_COUNT = 0;
const uint8_t DEPTH = 6;

[[noreturn]] int main(int argc, char *argv[]) 
{
        Interface inter;
        std::string move;
        bool verbose = (argc == 2) && (!strcmp(argv[1], "-v"));
        
        while(std::cin >> move){                
                inter.custom_move(move);
                
                if (MOVE_COUNT != 0 && verbose) {
                        std::cout << "LOOKED at "
                                  << MOVE_COUNT/1000
                                  << "K POSITIONS in\n"
                                  << TIME_TAKEN/1000
                                  << "ms\n";
                        MOVE_COUNT = 0;
                }
        }
}
