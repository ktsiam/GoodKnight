#ifndef MOVE_H_
#define MOVE_H_

#include "basic.h"
#include <vector>

class Move {

public:

        Move() = default;
        Move(uint32_t _data);
        Move(BB org, BB dest, Piece myP, Castling *c_rights, BB en_p_st, 
             Piece theirP = NO_PIECE, Castling cstl = NO_CASTLING,
             Piece promo = NO_PIECE, bool en_p = false);
        
        bool
        operator==(Move mv);
        operator uint32_t();
        
        bool is_quiet()          const;  // returns if move is quiet 
        Castling is_castling()   const;  // returns castling type of move
        bool is_en_passant()     const;  // returns if move is en_passant
        BB dest()                const;  // returns BB with destination
        BB origin()              const;  // returns BB with origin
        Piece my_piece()         const;  // returns piece moved
        Piece their_piece()      const;  // returns piece captured (if)
        Piece promoted_piece()   const;  // returns promoted piece type

        Castling castle_rights(Color) const;  // returns previous castle rights
        BB en_passant_status(Color)   const;  // returns previous en_passant square
        
private:

        uint32_t data;        //2 bits free
};

#endif // MOVE_H_

