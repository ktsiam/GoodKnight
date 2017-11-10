#include <iostream>

#include "basic.h"
#include "board.h"

void print(BB b);
void move(Board &b, std::string sq, std::string sq2, Piece p);
void move_r(Board &b, std::string sq, std::string sq2, Piece p);
void test_en_passant();
void test_opening();

int main()
{
        test_opening();
        test_en_passant();
}


void test_en_passant()
{
        Board b;

        std::cout << "EN-PASSANT GAME\n";
        b.print();
        move(b, "E2", "E4", PAWN);
        move(b, "E7", "E6", PAWN);
        move(b, "E4", "E5", PAWN);
        move(b, "D7", "D5", PAWN);

        b.front_move(Move{ SQ("E5"), SQ("D6"), PAWN, PAWN,
                                true, NO_CASTLING, NO_PIECE, true});
        b.print();

        b.init_variables();
        std::cout << "POSSIBLE KNIGHT MOVES\n";
        print(b.knight_move_gen());
        std::cout << "POSSIBLE KING MOVES\n";
        print(b.king_move_gen());


        std::cout << "REVERSING MOVES\n";
        b.back_move(Move{ SQ("E5"), SQ("D6"), PAWN, PAWN,
                                true, NO_CASTLING, NO_PIECE, true});
        b.print();
        move_r(b, "D7", "D5", PAWN);
        move_r(b, "E4", "E5", PAWN);
        move_r(b, "E7", "E6", PAWN);
        move_r(b, "E2", "E4", PAWN);
}

void test_opening()
{
        Board b;

        std::cout << "OPENING GAME\n";
        b.print();
        move(b, "E2", "E4", PAWN);
        move(b, "E7", "E5", PAWN);
        move(b, "G1", "F3", KNIGHT);
        move(b, "B8", "C6", KNIGHT);
        move(b, "F1", "C4", BISHOP);
        move(b, "F8", "C5", BISHOP);

        b.front_move(Move{0, 0, NO_PIECE, NO_PIECE, 0, O_O});
        b.print();

        b.init_variables();
        std::cout << "POSSIBLE KNIGHT MOVES\n";
        print(b.knight_move_gen());
        std::cout << "POSSIBLE KING MOVES\n";
        print(b.king_move_gen());

        std::cout << "REVERSING MOVES\n";
        b.back_move(Move{0, 0, NO_PIECE, NO_PIECE, 0, O_O, NO_PIECE, 0, BOTH});
        b.print();

        move_r(b, "F8", "C5", BISHOP);
        move_r(b, "F1", "C4", BISHOP);
        move_r(b, "B8", "C6", KNIGHT);
        move_r(b, "G1", "F3", KNIGHT);
        move_r(b, "E7", "E5", PAWN);
        move_r(b, "E2", "E4", PAWN);
}

void move(Board &b, std::string sq, std::string sq2, Piece p)
{
        Move mv(SQ(sq), SQ(sq2), p);
        b.front_move(mv);
        b.print();
}

void move_r(Board &b, std::string sq, std::string sq2, Piece p)
{
        Move mv(SQ(sq), SQ(sq2), p);
        b.back_move(mv);
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

//GENERATED MOVE GRAPHS
void gen_move()
{
        BB KNIGHT_MOVE[8][8];
        for (int y = 0; y < DIM; ++y){
                for (int x = 0; x < DIM; ++x) {
                        KNIGHT_MOVE[x][y] = 0;
                        if (x < 6 && y < 7)
                                KNIGHT_MOVE[x][y] |= shiftBB(1, x+2, y+1);
                        if (x < 6 && y >= 1)
                                KNIGHT_MOVE[x][y] |= shiftBB(1, x+2, y-1);
                        if (x < 7 && y < 6)
                                KNIGHT_MOVE[x][y] |= shiftBB(1, x+1, y+2);
                        if (x < 7 && y >= 2)
                                KNIGHT_MOVE[x][y] |= shiftBB(1, x+1, y-2);
                        if (x >= 1 && y < 6)
                                KNIGHT_MOVE[x][y] |= shiftBB(1, x-1, y+2);
                        if (x >= 1 && y >= 2)
                                KNIGHT_MOVE[x][y] |= shiftBB(1, x-1, y-2);
                        if (x >= 2 && y < 7)
                                KNIGHT_MOVE[x][y] |= shiftBB(1, x-2, y+1);
                        if (x >= 2 && y >= 1)
                                KNIGHT_MOVE[x][y] |= shiftBB(1, x-2, y-1);

                        //print(KNIGHT_MOVE[x][y]);
                        std::cout << (void *)KNIGHT_MOVE[x][y] << ", ";
                }
                std::cout << std::endl;
        }
}

