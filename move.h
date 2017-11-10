#ifndef MOVE_H_
#define MOVE_H_

#include "basic.h"

class Move {        

public:

        Move(BB org, BB dest, Piece myP = PAWN, Piece theirP = NO_PIECE, 
             bool capt = false, Castling cstl = NO_CASTLING, 
             Piece promo = NO_PIECE, bool en_p = false);

        Castling is_castling();
        bool is_capture();
        bool is_en_passant();
        BB dest();
        BB origin();
        Piece my_piece();
        Piece their_piece(); 
        Piece promoted_piece();


private:

        //TODO: INCREASE EFFICIENCY OF HOW INFORMATION IS STORED
        //use helper functions from basic.h

        BB orgn;
        BB destination;
        Piece my_pce;
        Piece their_pce;
        bool capture;
        Castling castling;
        Piece promotion;
        bool en_passant;
};


#endif // MOVE_H_

