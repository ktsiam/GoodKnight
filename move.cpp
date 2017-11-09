#include "move.h"

Move::Move(BB org, BB dest, Piece p, Castling c, BB en_p):
        pieces{ p }, castling{ c }, en_passant{ get_idx(en_p) }, 
        dest{ get_idx(dest) }, origin{ get_idx(org) } { };

uint8_t  Move::get
BB       Move::get_dest()       { return get_BB(dest);       }
BB       Move::get_origin()     { return get_BB(origin);     }
BB       Move::get_en_passant() { return en_passant ? get_BB(en_passant) : 0; }
Piece    Move::get_myPiece()    { return pieces;             }
Piece    Move::get_theirPiece() { return theirPiece;         }
Castling Move::get_castling()   { return castling;           }
