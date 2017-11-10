#ifndef BOARD_H_
#define BOARD_H_

#include "basic.h"
#include "move.h"
#include <vector>

class Board {
public:
        Board();
        void front_move(Move mv);

        //testing funcs
        void print();

protected:

        //position
        BB pieces[PIECE_NB][CLR_NB];

        //info
        Color clr;
        Castling castle_rights[CLR_NB];
        BB en_passant_sq;

        //helper
        void castle(Castling cstl, Color c);
        void en_passant(BB org, BB dest, Color c);
        void capture(BB dest, Piece pce, Color c);
        void promote(BB org, BB dest, Piece new_pce, Color c);
        void displace(BB org, BB dest, Piece pce, Color c);
        void set_en_passant(BB org, BB dest);
};


#endif // BOARD_H_
