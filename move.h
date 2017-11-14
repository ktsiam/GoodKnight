#ifndef MOVE_H_
#define MOVE_H_

#include "basic.h"

class Move {

public:

        Move(BB org, BB dest, Piece myP, Castling c_rights, BB en_p_st, 
             Piece theirP = NO_PIECE, Castling cstl = NO_CASTLING,
             Piece promo = NO_PIECE, bool en_p = false);

        Castling is_castling()   const;  // returns castling type of move
        bool is_en_passant()     const;  // returns if move is en_passant
        BB dest()                const;  // returns BB with destination
        BB origin()              const;  // returns BB with origin
        Piece my_piece()         const;  // returns piece moved
        Piece their_piece()      const;  // returns piece captured (if)
        Piece promoted_piece()   const;  // returns promoted piece type

        Castling castle_rights() const;  // returns previous castle rights
        BB en_passant_status()   const;  // returns previous en_passant square


protected:

        //TODO: INCREASE EFFICIENCY OF HOW INFORMATION IS STORED
        //use helper functions from basic.h

        BB orgn;            //6 bits
        BB destination;     //6 bits
        Piece my_pce;       //3 bits
        Castling rights;    //2 bits
        BB en_pass_status;  //6 bits
        Piece their_pce;    //3 bits
        Castling castling;  //2 bits
        Piece promotion;    //3 bits
        bool en_passant;    //1 bit
                            //total : 32 bits (yeyyy!)
};


#endif // MOVE_H_

