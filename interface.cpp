#include "interface.h"

#include <iostream>

using std::string;

static string to_str  (Move mv);
static string to_utf8 (Piece p, Color c);
static string to_ascii(BB b);


Interface::Interface()
{
        init_moves(false);
        init_move_str();
}

void Interface::interactive()
{
        render_board();
        
        enum COMMANDS { CPU_MOVE, PLAYER_MOVE, ANALYSIS, UNDO, QUIT };
        auto decode = [](std::string s) {
                if (s == "q" || s == "Q" || s == "quit")     return QUIT;
                if (s == "u" || s == "U" || s == "undo")     return UNDO;
                if (s == "a" || s == "A" || s == "analysis") return ANALYSIS;
                if (s == "c" || s == "C" || s == "cpu")      return CPU_MOVE;
                return PLAYER_MOVE;
        };

        std::string inp;
        while (std::cin >> inp)
                switch (decode(inp)) {
                        case UNDO        : undo();           break;
                        case ANALYSIS    : analysis();       break;
                        case CPU_MOVE    : computer_move();  break;
                        case PLAYER_MOVE : player_move(inp); break;
                        case QUIT        : return;
        }
}

void Interface::one_player()
{
        render_board();
        std::string move;
        
        while(std::cin >> move) {
                if (!player_move(move)) continue;
                computer_move();
        }
}

void Interface::two_player()
{
        render_board();
        
        std::string move;
        while(std::cin >> move)
                player_move(move);
}

void Interface::init_move_str()
{
        move_str.clear();
        for (Move mv : move_vec)
                move_str.push_back(to_str(mv));
}

void Interface::analysis()
{
        analyze();
        render_analysis();
        render_board();
}

void Interface::computer_move()
{
        analyze();
        front_move(best_move);
        render_board();
}

bool Interface::player_move(string str)
{
        init_moves(false);
        init_move_str();

        if (str == "0-0"   || str == "o-o")   str = "O-O";
        if (str == "0-0-O" || str == "o-o-o") str = "O-O-O";
        
        for (uint i = 0; i < move_str.size(); ++i)
                if (move_str[i] == str) {
                        front_move(move_vec[i]);
                        render_board();
                        return true;
                }
        render_moves();
        render_board();
        return false;
}

void Interface::undo()
{
        if (!history.empty())
                back_move();
        render_board();
}

void Interface::render_analysis()
{
        std::cout << "MOVE  : " << to_str(best_move) << std::endl
                  << "VALUE : " << ((clr == WHITE)? 1 : -1) * best_evaluation / 100.0
                  << std::endl;
}

void Interface::render_moves()
{
        int count = 0;
        for (std::string mv : move_str) 
                std::cout << mv << " \n"[count++ % 5 == 4];

        std::cout << std::endl;
}

void Interface::render_board()
{
        init_moves(false);
        std::cout << "   "
                  << ((castle_rights[BLACK] == BOTH)  ? "O-O & O-O-O  ":
                      (castle_rights[BLACK] == O_O)   ? "O-O          ":
                      (castle_rights[BLACK] == O_O_O) ? "O-O-O        ":
                      "              ")
                  << (en_passant_sq ? to_ascii(en_passant_sq) : "  ")
                  << ((clr == BLACK)? "  \u261A    " :"    ")
                  << std::endl;
        
        std::cout << "  -----------------\n";
        for (int r = DIM-1; r >= 0; --r){
                std::cout << r+1 << "| ";
                for (int f = 0; f < DIM; ++f) {
                        BB sq = File(f) & Rank(r);
                        string        p = to_utf8(find_piece(sq, WHITE), WHITE);
                        if (p == "\u00B7") p = to_utf8(find_piece(sq, BLACK), BLACK);
                        std::cout << p << " ";
                }
                std::cout << "|\n";
        }
        std::cout << "  -----------------\n"
                  << "   A B C D E F G H  "
                  << ((clr == WHITE) ? "\u261C\n" : " \n")
                  << "   " 
                  << ((castle_rights[WHITE] == BOTH)  ? "O-O & O-O-O\n":
                      (castle_rights[WHITE] == O_O)   ? "O-O\n":
                      (castle_rights[WHITE] == O_O_O) ? "O-O-O\n" : "\n");
}



static string to_ascii(BB b)
{
        Sq_idx  idx  = get_idx(b);
        uint8_t file = idx % DIM;
        uint8_t rank = idx / DIM;

        std::string sq;
        sq += "abcdefgh"[file];
        sq += "12345678"[rank];
        return sq;
}

static string to_str(Move mv)
{
        switch (mv.is_castling()) {
        case O_O   : return "O-O"  ; break;
        case O_O_O : return "O-O-O"; break;
        default    :                 break;
        }
        
        string s;
        s += to_ascii(mv.origin());
        s += to_ascii(mv.dest());
        return s;
                
}

static std::string to_utf8(Piece p, Color c)
{        
        if (c == WHITE) {
                switch (p) {
                case KING   : return "\u2654";
                case QUEEN  : return "\u2655";
                case ROOK   : return "\u2656";
                case BISHOP : return "\u2657";
                case KNIGHT : return "\u2658";
                case PAWN   : return "\u2659";
                default     : return "\u00B7";
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
                default     : return "\u00B7";
                }
        }
}
