#include "move.h"

Move::Move(BB org, BB dest, Piece myP, Piece theirP, 
           bool capt, Castling cstl, Piece promo, 
           bool en_p, Castling c_rights) :
        
        orgn(org), destination(dest), my_pce(myP),
        their_pce(theirP), capture(capt), castling(cstl),
        promotion(promo), en_passant(en_p), 
        rights(c_rights) { };
        
Castling Move::is_castling()    const { return castling;    }
bool     Move::is_capture()     const { return capture;     }
bool     Move::is_en_passant()  const { return en_passant;  }
BB       Move::dest()           const { return destination; }
BB       Move::origin()         const { return orgn;        }
Piece    Move::my_piece()       const { return my_pce;      }
Piece    Move::their_piece()    const { return their_pce;   }
Piece    Move::promoted_piece() const { return promotion;   }
Castling Move::castle_rights()  const { return rights;      }
