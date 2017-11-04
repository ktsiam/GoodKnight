#ifndef MOVE_H_
#define MOVE_H_

#include "basic.h"

class Move {        

public:
        Move(BB org, BB dest, Piece p, Castling c = NO_CASTLING, BB en_p = 0);
        BB get_dest();
        BB get_origin();
        BB get_en_passant();
        Piece get_piece();
        Castling get_castling();

private:
        Piece piece;
        Castling castling;
        Sq_idx en_passant;
        Sq_idx dest;
        Sq_idx origin;
};


#endif // MOVE_H_

