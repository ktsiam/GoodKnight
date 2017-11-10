#ifndef MOVE_H_
#define MOVE_H_

#include "basic.h"

class Move {

public:

        Move(BB org, BB dest, Piece myP = PAWN, Piece theirP = NO_PIECE,
             bool capt = false, Castling cstl = NO_CASTLING,
             Piece promo = NO_PIECE, bool en_p = false,
             Castling c_rights = BOTH, BB en_p_st = 0);

        Castling is_castling() const;
        bool is_capture() const;
        bool is_en_passant() const;
        BB en_passant_status() const;
        BB dest() const;
        BB origin() const;
        Piece my_piece() const;
        Piece their_piece() const;
        Piece promoted_piece() const;
        Castling castle_rights() const;


protected:

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
        Castling rights;
        BB en_pass_status;
};


#endif // MOVE_H_

