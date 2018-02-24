#include "move_maker.h"

////////////////////////////// PUBLIC /////////////////////////////

// MOVE MAKING FUNCTIONS

bool Move_maker::front_move(const Move mv)
{
        //capture  (en_passant is NOT a capture)
        if (mv.their_piece() != NO_PIECE)
                if (!capture(mv.dest(), mv.their_piece(), clr))
                        return false;

        //castling
        if (mv.is_castling() != NO_CASTLING) {
                castle(mv.is_castling(), clr);
                castle_rights[clr] = NO_CASTLING;
        }

        //en-passant  (also disable flag)
        else if (en_passant_sq = 0, mv.is_en_passant()) 
                en_passant(mv.origin(), mv.dest(), clr);        

        //promotion
        else if (mv.promoted_piece() != NO_PIECE)
                        promote(mv.origin(), mv.dest(), mv.promoted_piece(), clr);

        //displacement
        else {
                displace(mv.origin(), mv.dest(), mv.my_piece(), clr);

                //checking for future en-passant & castling rights
                switch (mv.my_piece()) {
                        case PAWN :
                                set_en_passant(mv.origin(), mv.dest()); break;
                        case KING :
                                castle_rights[clr] = NO_CASTLING;       break;
                        case ROOK : { 
                                bool o_o   = pieces[clr][ROOK] & shiftBB(1, 7, 7*clr);
                                bool o_o_o = pieces[clr][ROOK] & shiftBB(1, 0, 7*clr);
                                castle_rights[clr] = (Castling)
                                        ((o_o | (o_o_o << 1)) & castle_rights[clr]);
                        }
                        default : break;
                }
        }
       
        //swaping color
        clr = (Color) !clr;

        history.push(mv); //copy and swap
        return true;
}

void Move_maker::back_move()
{
        const Move mv = history.top();
        history.pop();

        //swapping color, adjusting Castling & en_passant
        clr = (Color) !clr;
        en_passant_sq      = mv.en_passant_status();
        castle_rights[clr] = mv.castle_rights();

        //capture (en_passant is NOT a capture)
        if (mv.their_piece() != NO_PIECE)
                capture(mv.dest(), mv.their_piece(), clr);

        //castling
        if (mv.is_castling() != NO_CASTLING)
                castle(mv.is_castling(), clr);

        //en-passant
        else if (mv.is_en_passant())
                en_passant(mv.origin(), mv.dest(), clr);

        //promotion
        else if (mv.promoted_piece() != NO_PIECE)
                        promote(mv.origin(), mv.dest(), mv.promoted_piece(), clr);

        //displacement
        else
                displace(mv.origin(), mv.dest(), mv.my_piece(), clr);
}


////////////////////////////// PRIVATE /////////////////////////////


// HELPERS

void Move_maker::castle(Castling cstl, Color c)
{
        int8_t opposite = (c == WHITE) ? 0 : 7;
        if (cstl == O_O) {
                pieces[c][KING] ^= shiftBB(0b101, 4, opposite);
                pieces[c][ROOK] ^= shiftBB(0b101, 5, opposite);
        }
        else {
                pieces[c][KING] ^= shiftBB(0b101,  2, opposite);
                pieces[c][ROOK] ^= shiftBB(0b1001, 0, opposite);
        }
}

void Move_maker::en_passant(BB org, BB dest, Color c)
{
        int8_t dir = (c == WHITE) ? -1 : 1;
        pieces[c][PAWN]   ^= org | dest;
        pieces[c^1][PAWN] ^= shiftBB(dest, 0, dir);
}

bool Move_maker::capture(BB dest, Piece pce, Color c)
{
        if (pce == KING) return false;
        pieces[c^1][pce] ^= dest;
        return true;
}

void Move_maker::promote(BB org, BB dest, Piece new_pce, Color c)
{
        pieces[c][PAWN]    ^= org;
        pieces[c][new_pce] ^= dest;
}

void Move_maker::displace(BB org, BB dest, Piece pce, Color c)
{
        pieces[c][pce] ^= org | dest;
}

void Move_maker::set_en_passant(BB org, BB dest)
{
        if (shiftBB(org, 0, 2) == dest)
                en_passant_sq = shiftBB(org, 0, 1);
        else if (shiftBB(org, 0, -2) == dest)
                en_passant_sq = shiftBB(org, 0, -1);
        else
                en_passant_sq = 0;
}

