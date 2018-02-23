#include "interface.h"

#include <iostream>

static std::string to_lowercase(std::string s);
static std::string sq_to_str (BB b);
static char        piece_to_char(Piece p);
static std::string piece_to_str(Piece p, Color c);

Interface::Interface()
{
        init_moves();
        init_move_str();
        print();
}
    
void Interface::sanity_check()
{
        checkmate();
        stalemate();
}

void Interface::custom_move(std::string str)
{
        if (str == "q" || str == "Q") {
                exit(0);
        }
        if (str == "r" || str == "R") {
                undo(); undo();
                init_moves();
                init_move_str();
                print();
                return;
        }        

        for (uint i = 0; i < move_str.size(); ++i)
                if (to_lowercase(str) == to_lowercase(move_str[i])) {
                        front_move(move_vec[i]); // our move
                        sanity_check();
                        print();
                        
                        front_move(best_move()); // their move
                        sanity_check();
                        print();
                        
                        init_move_str();
                        return;
                }
        std::cout << "Please Choose a valid move:\n";
        print_moves();
}

void Interface::checkmate()
{        
        init_moves();
        if (pieces[clr][KING] & team_movement[clr^1]) {
                for (auto it = move_vec.begin(); it != move_vec.end(); ++it)
                        if (it -> my_piece() == KING) return;
        } else return;
        
        std::cout << "CHECKMATE" << std::endl;                
}

void Interface::stalemate() //called after checkmate
{
        init_moves();
        if (move_vec.empty())
                std::cout << "STALEMATE" << std::endl;
}

void Interface::init_move_str()
{
        move_str.clear();
        for (auto it = move_vec.begin(); it != move_vec.end(); ++it) {
                if (it -> is_castling()) {
                        if (it -> is_castling() == O_O)
                                move_str.push_back("O-O");
                        else
                                move_str.push_back("O-O-O");
                        continue;
                }
                std::string new_mv = "";
                BB origin = it -> origin();
                BB dest   = it -> dest();
                bool capture = it -> their_piece() != NO_PIECE;
                Piece my_piece = it -> my_piece();

                if (my_piece != PAWN)
                        new_mv.push_back(piece_to_char(my_piece));
                else
                        if (capture || it -> is_en_passant())
                                new_mv.push_back(sq_to_str(origin)[0]);

                if (capture || it -> is_en_passant())
                        new_mv.push_back('x');

                new_mv += sq_to_str(dest);

                Piece promotion = it -> promoted_piece();
                if (promotion != NO_PIECE) {
                        new_mv.push_back('=');
                        new_mv.push_back(piece_to_char(promotion));
                }
                move_str.push_back(new_mv);
        }
}

void Interface::print_moves()
{
        int count = 0;
        for (auto it = move_str.begin(); it != move_str.end(); ++it, ++count)
                std::cout << *it << " \n"[count == 10];
        std::cout << std::endl;
}

void Interface::undo()
{
        if (!history.empty())
                back_move();
}

static std::string sq_to_str(BB b)
{
        int i = get_idx(b);
        int file = i%DIM;
        int rank = i/DIM;

        std::string sq = "";
        sq.push_back("abcdefgh"[file]);
        sq.push_back("12345678"[rank]);
        return sq;
}

static char piece_to_char(Piece p)
{
        return "KQRBNP  "[p];
}

static std::string piece_to_str(Piece p, Color c)
{
        if (c == WHITE) {
                switch (p) {
                case KING   : return "\u2654";
                case QUEEN  : return "\u2655";
                case ROOK   : return "\u2656";
                case BISHOP : return "\u2657";
                case KNIGHT : return "\u2658";
                case PAWN   : return "\u2659";
                default     : return "-";
                }
        }
        else {
                switch (p) {
                case KING   : return "\u265A";
                case QUEEN  : return "\u265B";
                case ROOK   : return "\u265C";
                case BISHOP : return "\u265D";
                case KNIGHT : return "\u265E";
                case PAWN   : return "\u265F";
                default     : return "-";
                }
        }
}

static std::string to_lowercase(std::string s)
{
        std::string lower = "";
        for (auto it = s.begin(); it != s.end(); ++it)
                lower.push_back(tolower(*it));
        return lower;
}

void Interface::print()
{
        std::cout << ((clr==WHITE)?"\nWHITE   ":"\nBLACK   ")
                  << ((castle_rights[BLACK] == BOTH)  ? "O-O & O-O-O  ":
                      (castle_rights[BLACK] == O_O)   ? "O-O          ":
                      (castle_rights[BLACK] == O_O_O) ? "O-O-O        ":
                                                        "             ")
                  << (en_passant_sq ? sq_to_str(en_passant_sq) : "")
                  << std::endl;
        
        std::cout << "  -----------------\n";
        for (int r = DIM-1; r >= 0; --r){
                std::cout << r+1 << "| ";
                for (int f = 0; f < DIM; ++f) {
                        BB sq = File(f) & Rank(r);

                        std::string p = piece_to_str(find_piece(sq, WHITE), WHITE);
                        if (p == "-") 
                                p = piece_to_str(find_piece(sq, BLACK), BLACK);
                        std::cout << p << " ";

                }
                std::cout << "|\n";
        }
        std::cout << "  -----------------\n";
        std::cout << "   A B C D E F G H\n        ";
        std::cout << ((castle_rights[WHITE] == BOTH)  ? "O-O & O-O-O\n":
                      (castle_rights[WHITE] == O_O)   ? "O-O\n":
                      (castle_rights[WHITE] == O_O_O) ? "O-O-O\n" : "\n");
}
