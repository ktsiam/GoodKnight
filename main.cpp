#include <iostream>
#include "test_board.h"

unsigned MOVE_COUNT = 0;
const uint8_t DEPTH = 3;

[[noreturn]] int main() 
{
        Test_board b;
        b.print();

        std::string move;
        while(std::cin >> move){
                b.custom_move(move);
                std::cout << MOVE_COUNT << std::endl;
        }
}
