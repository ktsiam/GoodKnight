#include "move.h"

Move::Move(BB org, BB dest, Piece p, Castling c = NO_CASTLING, BB en_p = 0):
        piece{ p }, castling{ c }, en_passant{ en_p }, 
        dest{ get_idx(dest) }, origin{ get_idx(org) } { };

BB       Move::get_dest()       { return get_BB(dest);       }
BB       Move::get_origin()     { return get_BB(origin);     }
BB       Move::get_en_passant() { return get_BB(en_passant); }
Piece    Move::get_piece()      { return piece;              }
Castling Move::get_castling()   { return castling;           }
