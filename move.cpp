#include "move.h"

Move::Move(BB org, BB dest, Piece myP, Piece theirP, 
     bool capt = false, Castling cstl = NO_CASTLING, 
     Piece promo = NO_PIECE, bool en_p = false) :
        
        origin(org), destination(dest), my_piece(myP),
        their_piece(theirP), capture(capt), castling(cstl),
        promotion(promo), en_passant(en_p) { };
        
Castling is_castling() { return castling; }
bool is_capture() { return capture; }
bool is_en_passant() { return en_passant; }
BB dest() { return destination; }
BB origin() { return origin; }
Piece my_piece() { return my_piece; }
Piece their_piece() { return their_piece; }
Piece promoted_piece() { return promoted_piece; }
