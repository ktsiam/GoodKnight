#ifndef MOVE_H_
#define MOVE_H_

#include "basic.h"

class Move {

public:
        Move(BB org, BB dest, Piece p, Castling c = NO_CASTLING, uint8_t en_p = 0);

private:
        Sq_idx dest;
        Sq_idx origin;
        Piece piece;
        Castling castling;
        Sq_idx en_passant;
};


#endif // MOVE_H_

//ADD FROM TO AND RETURN BITBOARDS
