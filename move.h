#ifndef MOVE_H_
#define MOVE_H_

#include "basic.h"

class Move {        

public:
        Move(BB org, BB dest, Piece p, Castling c = NO_CASTLING, BB en_p = 0);
        BB get_dest();
        BB get_origin();
        BB get_en_passant();
        Piece get_myPiece();
        Piece get_theirPiece();
        Castling get_castling();
        uint8_t get_flag();

private:
        Piece myPiece;
        Piece theirPiece;
        Sq_idx dest;
        Sq_idx origin;

        uint8_t flag; // 0          -     000    -    00    -    0    
                      // en passant -  promotion - castling - capture 

        Sq_idx en_passant;
};


#endif // MOVE_H_

