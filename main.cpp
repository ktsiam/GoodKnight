#include <iostream>

#include "basic.h"
#include "board.h"

void print(BB);
void move(Board &b, std::string sq, std::string sq2, Piece p);
void test_en_passant();
void test_opening();

int main()
{
        std::cout << "TESTING OPENING SEQUENCE\n\n";
        test_opening();
        std::cout << "\n\n\nTESTING EN PASSANT\n\n";
        test_en_passant();
}
void test_en_passant()
{
        Board b;
        b.print();
        move(b, "E2", "E4", PAWN);
        move(b, "E7", "E6", PAWN);
        move(b, "E4", "E5", PAWN);
        move(b, "D7", "D5", PAWN);
        
        b.front_move(Move{ SQ("E5"), SQ("D6"), PAWN, PAWN, 
                                true, NO_CASTLING, NO_PIECE, true});

        b.print();
}

void test_opening()
{
        Board b;
        b.print();
        move(b, "E2", "E4", PAWN);
        move(b, "E7", "E5", PAWN);
        move(b, "G1", "F3", KNIGHT);
        move(b, "B8", "C6", KNIGHT);
        move(b, "F1", "C4", BISHOP);
        move(b, "F8", "C5", BISHOP);

        b.front_move(Move{0, 0, NO_PIECE, NO_PIECE, 0, O_O});
        b.print();
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

void move(Board &b, std::string sq, std::string sq2, Piece p)
{
        Move mv(SQ(sq), SQ(sq2), p);
        b.front_move(mv);
        b.print();
}
