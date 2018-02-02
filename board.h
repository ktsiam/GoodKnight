#ifndef BOARD_H_
#define BOARD_H_

#include "basic.h"
#include "move.h"
#include <vector>
#include <stack>

class Board {
public:
        Board();
        void front_move(const Move mv);
        void back_move ();

        void init_moves();
        std::vector<Move> move_vec;

protected:

        Piece find_piece(BB sq, Color c);

        //position
        BB pieces[CLR_NB][PIECE_NB];
        Color clr;
        Castling castle_rights[CLR_NB];
        BB en_passant_sq;

        //move history
        std::stack<Move> history;
private:


        //temporary variables (re-evaluated each position)
        BB all_pieces;
        BB team_pieces[CLR_NB];

        //move generators
        void castling_gen();
        void king_move_gen();
        void knight_move_gen();
        void pawn_move_gen();
        void rook_move_gen();
        void bishop_move_gen();
        void queen_move_gen();

        //static generator helpers
        void general_move_gen(BB origin, Piece pce, BB moves);
        void en_passant_gen(BB pawns);
        void promotion_gen(BB origin, BB dest, Piece = NO_PIECE);
        void double_move_gen(BB origin);
        void pawn_attack_gen(BB origin);
        void pawn_non_attack_gen(BB origin);

        //sliding generator helpers
        void rank_move_gen(BB origin, Piece pce);
        void file_move_gen(BB origin, Piece pce);
        void diagonal_move_gen(BB origin, Piece pce);
        void antidiag_move_gen(BB origin, Piece pce);
        uint8_t byte_bb_gen      (uint8_t orig, uint8_t occup);
        uint8_t byte_bb_gen_left (uint8_t orig, uint8_t occup);
        uint8_t byte_bb_gen_right(uint8_t orig, uint8_t occup);

        //front-back move helpers
        void castle(Castling cstl, Color c);
        void en_passant(BB org, BB dest, Color c);
        void capture(BB dest, Piece pce, Color c);
        void promote(BB org, BB dest, Piece new_pce, Color c);
        void displace(BB org, BB dest, Piece pce, Color c);
        void set_en_passant(BB org, BB dest);
};


#endif // BOARD_H_
