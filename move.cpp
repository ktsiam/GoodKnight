#include "move.h"

Move::Move(uint32_t _data) : data(_data) {};
Move::Move(BB org, BB dest, Piece myP, Castling *c_rights, 
           BB en_p_st, Piece theirP, Castling cstl, 
           Piece promo, bool en_p)
{
        data  = //general attributes
                  get_idx(dest)
                | get_idx(org)     << 6
                | myP              << 12
                | theirP           << 15
                | promo            << 18
                | cstl             << 21
                | (en_p ? 1 : 0)   << 23
                
                //for reversability
                | get_idx(en_p_st) % DIM << 24
                | (en_p_st != 0)         << 27
                | c_rights[WHITE]        << 28
                | c_rights[BLACK]        << 30;
}

bool Move::operator==(Move mv) { return data == mv.data; }
     Move::operator uint32_t() { return data; }

bool     Move::is_quiet()          const { return (their_piece() == NO_PIECE || is_en_passant());}   
Castling Move::is_castling()       const { return static_cast<Castling> (data >> 21 & 0x3      ); }
bool     Move::is_en_passant()     const { return static_cast<bool>     (data >> 23 & 0x1      ); }
BB       Move::dest()              const { return static_cast<BB>(get_BB(data       & 0x3F)    ); }
BB       Move::origin()            const { return static_cast<BB>(get_BB(data >> 6  & 0x3F)    ); }
Piece    Move::my_piece()          const { return static_cast<Piece>    (data >> 12 & 0x7      ); }
Piece    Move::their_piece()       const { return static_cast<Piece>    (data >> 15 & 0x7      ); }
Piece    Move::promoted_piece()    const { return static_cast<Piece>    (data >> 18 & 0x7      ); }
BB       Move::en_passant_status(Color c) const
{ return (data >> 27 & 0x1) ? File(data >> 24 & 0x7) & Rank(4-c):0;}
Castling Move::castle_rights    (Color c) const
{ return static_cast<Castling> (data >> ((c == WHITE) ? 28 : 30) & 0x3);}
