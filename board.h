#ifndef BOARD_H_
#define BOARD_H_

#include "basic.h"
#include "move.h"

class Board {
public:
        Board();
        void front_move(const Move mv);
        void back_move(const Move mv);
        //testing funcs
        void print();

private:

        //position
        BB pieces[CLR_NB][PIECE_NB];

        //info
        Color clr;
        Castling castle_rights[CLR_NB];
        BB en_passant_sq;

        //temporary variables (re-evaluated each position)
        BB all_pieces[CLR_NB];


        //move helper
        void castle(Castling cstl, Color c);
        BB   en_passant(BB org, BB dest, Color c);
        void capture(BB dest, Piece pce, Color c);
        void promote(BB org, BB dest, Piece new_pce, Color c);
        void displace(BB org, BB dest, Piece pce, Color c);
        void set_en_passant(BB org, BB dest);

public:
        //gen helper
        void init_variables();
        BB knight_move_gen();
        BB king_move_gen();
        //BB pawn_move_gen();
};


#endif // BOARD_H_
