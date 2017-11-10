#include "move.h"

Move::Move(BB org, BB dest, Piece myP, Piece theirP, 
     bool capt, Castling cstl, Piece promo, bool en_p) :
        
        orgn(org), destination(dest), my_pce(myP),
        their_pce(theirP), capture(capt), castling(cstl),
        promotion(promo), en_passant(en_p) { };
        
Castling Move::is_castling()    { return castling;    }
bool     Move::is_capture()     { return capture;     }
bool     Move::is_en_passant()  { return en_passant;  }
BB       Move::dest()           { return destination; }
BB       Move::origin()         { return orgn;        }
Piece    Move::my_piece()       { return my_pce;      }
Piece    Move::their_piece()    { return their_pce;   }
Piece    Move::promoted_piece() { return promotion;   }
