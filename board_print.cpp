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

void Board::custom_move(std::string str)
{
        if (str == "O-O") 
                return castle(O_O, clr);
        else if (str == "O-O-O")
                return castle(O_O_O, clr);
        
        Piece my_piece = char_to_piece(str[0]);
        if (my_piece == NO_PIECE)
                my_piece = PAWN;
        else
                str.erase(0);
        
        bool capture = (str[0] == 'x') || (str[0] == 'X');
        if (capture)
                str.erase(0);

        BB dest = str_to_sq(str.substr(0, 2));

        Piece promotion = NO_PIECE;
        if (str.find('=') != std::string::npos)
                promotion = char_to_piece(str.back());
                
        bool en_passant = true;
        Piece their_piece;
        if (capture) {
                their_piece = find_piece(dest, (Color) (clr^1));
                if (their_piece == NO_PIECE) {
                        en_passant = true;
                        capture    = false;
                }
        }
        else
                their_piece = NO_PIECE;

        BB origin = 3; //impossible
        
        for (auto it = move_vec.begin(); it != move_vec.end(); ++it) {
                if (it -> my_piece() == my_piece && it -> dest() == dest) {
                        origin = it -> origin();
                        break;
                }
        }
        
        if (origin == 3)
                std::cout << "INVALID MOVE\n";
        else {
                Move mv{origin, dest, my_piece, castle_rights[clr], en_passant_sq, 
                                their_piece, NO_CASTLING, promotion, en_passant};
                front_move(mv);
        }
                
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
