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
        void pawn_move_gen();


        //generator helper
        Piece find_piece(BB sq, Color c);

        //move helper
        void castle(Castling cstl, Color c);
        void en_passant(BB org, BB dest, Color c);
        void capture(BB dest, Piece pce, Color c);
        void promote(BB org, BB dest, Piece new_pce, Color c);
        void displace(BB org, BB dest, Piece pce, Color c);
        void set_en_passant(BB org, BB dest);
};


#endif // BOARD_H_
