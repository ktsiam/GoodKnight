#include "board.h"



Board::Board()
{
        pieces[K][0] = SQ("E1"),          pieces[K][1] = SQ("E8");
        pieces[Q][0] = SQ("D1"),          pieces[Q][1] = SQ("D8");
        pieces[R][0] = SQ("A1")|SQ("A8"), pieces[R][1] = SQ("H1")|SQ("H8");
        pieces[B][0] = SQ("C1")|SQ("F1"), pieces[B][1] = SQ("C8")|SQ("F8");
        pieces[N][0] = SQ("B1")|SQ("G1"), pieces[N][1] = SQ("B8")|SQ("G8");
        pieces[P][0] = Rank(1),           pieces[P][1] = Rank(6);

        clr = WHITE;
        en_passant = 0;
}

void Board::front_move(Move mv)
{        
        //CASTLING
        Castling cstl;
        if (cstl = mv.is_castling()) {
                uint8_t opposite = (clr == BLACK) * 7;
                if (castl == O_O) {
                        piece[KING][clr] ^= shiftBB(0b101, 4, opposite);
                        piece[ROOK][clr] ^= shiftBB(0b101, 5, opposite);
                }
                else {
                        piece[KING][clr] ^= shiftBB(0b101, 2, opposite);
                        piece[ROOK][clr] ^= shiftBB(0b1001, opposite);
                }                        
                return;
        }        

        //EN PASSANT
        if (mv.is_en_passant()) {
                BB dest = mv.dest();
                int8_t dir = (clr == WHITE) ? -1 : 1;
                piece[PAWN][clr]   ^= mv.origin() | mv.dest();             
                piece[PAWN][clr^1] ^= shiftBB(dest, 0, dir);
                return;
        }

        //CAPTURE
        if (mv.is_capture()) {
                piece[mv.their_piece()][clr^1] ^= mv.dest();
        }

        //PROMOTION
        Piece promoted;
        if (promoted = mv.promoted_piece()) {
                piece[PAWN][clr] ^= mv.origin();
                piece[promoted][clr] ^= mv.dest();               
                return;
        }

        //NORMAL MOVE
        piece[mv.my_piece()][clr] ^= mv.origin() | mv.dest();
}
