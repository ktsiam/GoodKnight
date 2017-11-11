#ifndef BOARD_H_
#define BOARD_H_

#include "basic.h"
#include "move.h"
#include <vector>

class Board {
public:
        Board();
        void front_move(const Move &mv);
        void back_move (const Move &mv);

        void print();

private:
        //move chains
        std::vector<Move> move_vec;        

        //position
        BB pieces[CLR_NB][PIECE_NB];
        Color clr;
        Castling castle_rights[CLR_NB];
        BB en_passant_sq;

        //temporary variables (re-evaluated each position)
        BB all_pieces[CLR_NB];


        //dependency
        void init_variables();

        //move generators
        void castling_gen();
        void king_move_gen();

        void knight_move_gen();
        void (Board::*pawn_move_gen[CLR_NB])() = 
        { &Board::pawn_white_move_gen, &Board::pawn_black_move_gen };


        //generator helpers
        Piece find_piece(BB sq, Color c);
        void general_move_gen(BB origin, Piece pce, BB moves);
        void pawn_black_move_gen();
        void pawn_white_move_gen();
        void en_passant_gen(BB pawns);
        void promotion_gen(BB origin, BB dest, Piece = NO_PIECE);
        void double_move_gen(BB origin);

        //move helper
        void castle(Castling cstl, Color c);
        void en_passant(BB org, BB dest, Color c);
        void capture(BB dest, Piece pce, Color c);
        void promote(BB org, BB dest, Piece new_pce, Color c);
        void displace(BB org, BB dest, Piece pce, Color c);
        void set_en_passant(BB org, BB dest);
};


#endif // BOARD_H_
