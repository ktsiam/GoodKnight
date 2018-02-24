#include "move_maker.h"

////////////////////////////// PUBLIC /////////////////////////////

// MOVE MAKING FUNCTIONS

void Move_maker::front_move(const Move mv)
{
        //capture  (en_passant is NOT a capture)
        if (mv.their_piece() != NO_PIECE)
                capture(mv.dest(), mv.their_piece());

        //castling
        if (mv.is_castling() != NO_CASTLING) {
                castle(mv.is_castling());
                castle_rights[clr] = NO_CASTLING;
        }

        //en-passant  (also disable flag)
        else if (en_passant_sq = 0, mv.is_en_passant()) 
                en_passant(mv.origin(), mv.dest());        

        //promotion
        else if (mv.promoted_piece() != NO_PIECE)
                        promote(mv.origin(), mv.dest(), mv.promoted_piece());

        //displacement
        else {
                displace(mv.origin(), mv.dest(), mv.my_piece());

                //checking for future en-passant & castling rights
                switch (mv.my_piece()) {
                        case PAWN :
                                set_en_passant(mv.origin(), mv.dest()); break;
                        case KING :
                                castle_rights[clr] = NO_CASTLING;       break;
                        case ROOK : {
                                if (castle_rights[clr]) check_castling(clr);
                        }
                        default : break;
                }
        }
       
        //swaping color
        clr = (Color) !clr;

        history.push(mv); //copy and swap
}

void Move_maker::back_move()
{
        const Move mv = history.top();
        history.pop();

        //swapping color, adjusting Castling & en_passant
        clr = static_cast<Color>(clr^1);
        en_passant_sq      = mv.en_passant_status();
        castle_rights[clr] = mv.castle_rights();

        //capture (en_passant is NOT a capture)
        if (mv.their_piece() != NO_PIECE)
                capture(mv.dest(), mv.their_piece());

        //castling
        if (mv.is_castling() != NO_CASTLING)
                castle(mv.is_castling());

        //en-passant
        else if (mv.is_en_passant())
                en_passant(mv.origin(), mv.dest());

        //promotion
        else if (mv.promoted_piece() != NO_PIECE)
                        promote(mv.origin(), mv.dest(), mv.promoted_piece());

        //displacement
        else
                displace(mv.origin(), mv.dest(), mv.my_piece());
}


////////////////////////////// PRIVATE /////////////////////////////


// HELPERS

void Move_maker::castle(Castling cstl)
{
        uint8_t shift = (clr == WHITE) ? 0 : 56;
        if (cstl == O_O) {
                pieces[clr][KING] ^= (0b101 << (shift + 4));
                pieces[clr][ROOK] ^= (0b101 << (shift + 5));
        }
        else {
                pieces[clr][KING] ^= (0b101  << (shift + 2));
                pieces[clr][ROOK] ^= (0b1001 << shift);
        }
}

void Move_maker::en_passant(BB org, BB dest)
{
        pieces[clr  ][PAWN]   ^= org | dest;
        pieces[clr^1][PAWN]   ^= (clr == WHITE) ? (dest >> 8) : (dest << 8);
}

void Move_maker::capture(BB dest, Piece pce)
{
        pieces[clr^1][pce] ^= dest;
        if ((pce == ROOK) && castle_rights[clr^1])
                check_castling((Color)(clr^1));
}

void Move_maker::promote(BB org, BB dest, Piece new_pce)
{
        pieces[clr][PAWN]    ^= org;
        pieces[clr][new_pce] ^= dest;
}

void Move_maker::displace(BB org, BB dest, Piece pce)
{
        pieces[clr][pce] ^= org | dest;
}

void Move_maker::set_en_passant(BB org, BB dest)
{
        if      ((clr == WHITE) && (org << 16) == dest)
                en_passant_sq = org << 8;
        else if ((clr == BLACK) && (org >> 16) == dest)
                en_passant_sq = org >> 8;
        else
                en_passant_sq = 0;
}

void Move_maker::check_castling(Color c)
{
        uint8_t shift = (c == WHITE) ? 0 : 56;
        bool o_o   = pieces[c][ROOK] & (1 << (shift + 7));
        bool o_o_o = pieces[c][ROOK] & (1 << (shift    ));
        castle_rights[c] = static_cast<Castling>
                ((o_o | (o_o_o << 1)) & castle_rights[clr]);
}
