#include <iostream>
#include "test_board.h"

void print(BB b);
int main()
{
        Test_board b;
        b.print();

        std::string move;
        while(std::cin >> move)
                b.custom_move(move);
}
