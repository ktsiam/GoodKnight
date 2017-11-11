#include "board.h"

#include <iostream>

static std::string sq_to_str(BB b)
{
        int i = get_idx(b);
        int file = i%DIM;
        int rank = i/DIM;

        std::string sq;
        sq.push_back("ABCDEFGH"[file]);
        return sq + "12345678"[rank];
}

static BB str_to_sq(std::string s)
{
        return File(s[0] - 'A') & Rank(s[1] - '1');
}

static char piece_to_char(Piece p)
{
        return "KQRBNP  "[p];
}

static Piece char_to_piece(char c)
{
        Piece p;
        switch(c){
                case 'K' : p = KING;     break;
                case 'Q' : p = QUEEN;    break;
                case 'R' : p = ROOK;     break;
                case 'B' : p = BISHOP;   break;
                case 'N' : p = KNIGHT;   break;
                case 'P' : p = PAWN;     break;
                default  : p = NO_PIECE; break;
        }
        return p;
}


void Board::print()
{
        std::cout << ((clr==WHITE)?"\nWHITE   ":"\nBLACK   ");
        std::cout << ((castle_rights[BLACK] == BOTH)  ? "O-O & O-O-O\n":
                      (castle_rights[BLACK] == O_O)   ? "O-O\n":
                      (castle_rights[BLACK] == O_O_O) ? "O-O-O\n" : "\n");

        std::cout << "  -----------------\n";
        for (int r = DIM-1; r >= 0; --r){
                std::cout << r+1 << "| ";
                for (int f = 0; f < DIM; ++f) {
                        BB sq = File(f) & Rank(r);

                        char p = piece_to_char(find_piece(sq, WHITE));
                        if (p == ' ') {
                                p = piece_to_char(find_piece(sq, BLACK));
                                if (p != ' ')
                                        p += 32;
                        }
                        std::cout << p << " ";
                        
                }
                std::cout << "|\n";
        }
        std::cout << "  -----------------\n";
        std::cout << "   A B C D E F G H\n        ";
        std::cout << ((castle_rights[WHITE] == BOTH)  ? "O-O & O-O-O\n":
                      (castle_rights[WHITE] == O_O)   ? "O-O\n":
                      (castle_rights[WHITE] == O_O_O) ? "O-O-O\n" : "\n");
        std::cout << "\n  #################\n\n";
}

void Board::printBB(BB b)
{
        for (int r = 7; r >= 0; --r){
                std::cout << r+1 << " ";
                for (int f = 0; f < 8; ++f)
                        std::cout << "_o"[(bool)(b & 1ULL << (8*r+f))] << " ";
                std::cout << "\n";
        }
        std::cout << "  A B C D E F G H\n\n";        
}

void Board::print_moves()
{
        init_moves();

        for (auto mv = move_vec.begin(); mv != move_vec.end(); ++mv) {
                if (mv -> is_castling()) 
                        std::cout << ((mv -> is_castling() == O_O)? "O-O" : "O-O-O");

                else if (mv -> is_en_passant())
                        std::cout << sq_to_str(mv -> origin())[0] << "x" 
                                  << sq_to_str(mv -> dest()) << " (en passant)";
                
                else {
                        std::string move = "";
                        
                        Piece p = mv -> my_piece();
                        if (p != PAWN)
                                std::cout << piece_to_char(p);
                        
                        if (mv -> their_piece() != NO_PIECE) {
                                if (mv -> their_piece() == PAWN)
                                        std::cout << (sq_to_str(mv -> origin())[0]);
                                std::cout << 'x';
                        }
                        
                        std::cout << sq_to_str(mv -> dest());
                        
                        if (mv -> promoted_piece() != NO_PIECE) {
                                std::cout << " = "
                                          << piece_to_char(mv -> promoted_piece());
                        }
                }
                std::cout << std::endl;
        }
}
