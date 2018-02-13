#include <iostream>

#include "test_board.h"

unsigned TIME_TAKEN;
unsigned MOVE_COUNT = 0;
const uint8_t DEPTH = 7;

[[noreturn]] int main() 
{
        Test_board b;
        b.print();

        std::string move;
        while(std::cin >> move){
                b.custom_move(move);
                std::cout << "LOOKED at "     << MOVE_COUNT/1000
                          << "K POSITIONS in\n" << TIME_TAKEN/1000
                          << "ms\n";
                MOVE_COUNT = 0;
        }
}
