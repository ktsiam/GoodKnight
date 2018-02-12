#include "board.h"

Board::Board()
{
        //position
        pieces[WHITE][KING]   = SQ("E1");          pieces[BLACK][KING]   = SQ("E8");
        pieces[WHITE][QUEEN]  = SQ("D1");          pieces[BLACK][QUEEN]  = SQ("D8");
        pieces[WHITE][ROOK]   = SQ("A1")|SQ("H1"); pieces[BLACK][ROOK]   = SQ("A8")|SQ("H8");
        pieces[WHITE][BISHOP] = SQ("C1")|SQ("F1"); pieces[BLACK][BISHOP] = SQ("C8")|SQ("F8");
        pieces[WHITE][KNIGHT] = SQ("B1")|SQ("G1"); pieces[BLACK][KNIGHT] = SQ("B8")|SQ("G8");
        pieces[WHITE][PAWN]   = Rank(1);           pieces[BLACK][PAWN]   = Rank(6);  

        
        clr = WHITE;
        en_passant_sq = 0;

        castle_rights[WHITE] = BOTH;
        castle_rights[BLACK] = BOTH;
}
