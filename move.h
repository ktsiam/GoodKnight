#ifndef MOVE_H_
#define MOVE_H_

#include "basic.h"

class Move {
        
public:
        
private:
        Sq_idx dest;
        Sq_idx origin;
        Castling castling;
        Piece piece;
        uint8_t spec_move;
};


#endif // MOVE_H_

//ADD FROM TO AND RETURN BITBOARDS
