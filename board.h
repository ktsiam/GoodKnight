#ifndef BOARD_H_
#define BOARD_H_

#include "basic.h"
#include "move.h"
#include <vector>

class Board {
public:
        Board();
        void front_move(Move mv);

protected:

        //position
        BB pieces[PIECE_NB][CLR_NB];

        //info
        Color clr;
        Castling castle_rights[CLR_NB];
        BB en_passant;

        //helper funcs
        void castle(Castling);
};


#endif // BOARD_H_
