#ifndef MOVE_H_
#define MOVE_H_

#include "basic.h"

struct Move {
        Sq_idx dest;
        Sq_idx origin;
        Castling castling;
        Piece piece;        
};


#endif // MOVE_H_
