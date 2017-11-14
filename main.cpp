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


void print(BB b)
{
        for (int r = 7; r >= 0; --r){
                std::cout << r+1 << " ";
                for (int f = 0; f < 8; ++f)
                        std::cout << "_o"[(bool)(b & 1ULL << (8*r+f))] << " ";
                std::cout << "\n";
        }
        std::cout << "  A B C D E F G H\n\n";
}
