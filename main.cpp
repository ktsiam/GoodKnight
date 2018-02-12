#include <iostream>
#include "test_board.h"

const uint8_t DEPTH = 5;

[[noreturn]] int main() 
{
        Test_board b;
        b.print();

        std::string move;
        while(std::cin >> move)
                b.custom_move(move);
}
