#include "board.h"

static BB SQ(std::string s)
{
        return File(s[0] - 'A') & Rank(s[1] - '1');
}

Board::Board()
{
        pieces[WHITE][KING]   = SQ("E1");          pieces[BLACK][KING]   = SQ("E8");
//        pieces[WHITE][QUEEN]  = SQ("D1");          pieces[BLACK][QUEEN]  = SQ("D8");
        pieces[WHITE][QUEEN]  = 0; pieces[BLACK][QUEEN]  = 0;
        pieces[WHITE][ROOK]   = SQ("A1")|SQ("H1"); pieces[BLACK][ROOK]   = SQ("A8")|SQ("H8");
//        pieces[WHITE][BISHOP] = SQ("C1")|SQ("F1"); pieces[BLACK][BISHOP] = SQ("C8")|SQ("F8");
        pieces[WHITE][BISHOP] = 0; pieces[BLACK][BISHOP] = 0;
        pieces[WHITE][KNIGHT] = SQ("B1")|SQ("G1"); pieces[BLACK][KNIGHT] = SQ("B8")|SQ("G8");
        pieces[WHITE][PAWN]   = Rank(1);           pieces[BLACK][PAWN]   = Rank(6);

        clr = WHITE;
        en_passant_sq = 0;

        castle_rights[WHITE] = BOTH;
        castle_rights[BLACK] = BOTH;
        
        init_moves();
}

void Board::front_move(const Move mv)
{
        //capture  (en_passant is NOT a capture)
        if (mv.their_piece() != NO_PIECE)
                capture(mv.dest(), mv.their_piece(), clr);

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
}

void Board::back_move()
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

void Board::castle(Castling cstl, Color c)
{
        int8_t opposite = (c == BLACK) * 7;
        if (cstl == O_O) {
                pieces[c][KING] ^= shiftBB(0b101, 4, opposite);
                pieces[c][ROOK] ^= shiftBB(0b101, 5, opposite);
        }
        else {
                pieces[c][KING] ^= shiftBB(0b101,  2, opposite);
                pieces[c][ROOK] ^= shiftBB(0b1001, 0, opposite);
        }
}

void Board::en_passant(BB org, BB dest, Color c)
{
        int8_t dir = (c == WHITE) ? -1 : 1;
        pieces[c][PAWN]   ^= org | dest;
        pieces[c^1][PAWN] ^= shiftBB(dest, 0, dir);
}

void Board::capture(BB dest, Piece pce, Color c)
{
        pieces[c^1][pce] ^= dest;
}

void Board::promote(BB org, BB dest, Piece new_pce, Color c)
{
        pieces[c][PAWN]    ^= org;
        pieces[c][new_pce] ^= dest;
}

void Board::displace(BB org, BB dest, Piece pce, Color c)
{
        pieces[c][pce] ^= org | dest;
}

void Board::set_en_passant(BB org, BB dest)
{
        if (shiftBB(org, 0, 2) == dest)
                en_passant_sq = shiftBB(org, 0, 1);
        else if (shiftBB(org, 0, -2) == dest)
                en_passant_sq = shiftBB(org, 0, -1);
        else
                en_passant_sq = 0;
}
