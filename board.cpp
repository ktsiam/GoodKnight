#include "board.h"



Board::Board()
{
        pieces[KING]  [0] = SQ("E1"),          pieces[KING] [1] = SQ("E8");
        pieces[QUEEN] [0] = SQ("D1"),          pieces[QUEEN] [1] = SQ("D8");
        pieces[ROOK]  [0] = SQ("A1")|SQ("H1"), pieces[ROOK]  [1] = SQ("A8")|SQ("H8");
        pieces[BISHOP][0] = SQ("C1")|SQ("F1"), pieces[BISHOP][1] = SQ("C8")|SQ("F8");
        pieces[KNIGHT][0] = SQ("B1")|SQ("G1"), pieces[KNIGHT][1] = SQ("B8")|SQ("G8");
        pieces[PAWN]  [0] = Rank(1),           pieces[PAWN]  [1] = Rank(6);

        clr = WHITE;
        en_passant = 0;
}

void Board::front_move(Move mv)
{        
        //CASTLING
        Castling cstl = mv.is_castling();
        if (cstl != NO_CASTLING) {
                uint8_t opposite = (clr == BLACK) * 7;
                if (cstl == O_O) {
                        pieces[KING][clr] ^= shiftBB(0b101, 4, opposite);
                        pieces[ROOK][clr] ^= shiftBB(0b101, 5, opposite);
                }
                else {
                        pieces[KING][clr] ^= shiftBB(0b101,  2, opposite);
                        pieces[ROOK][clr] ^= shiftBB(0b1001, 0, opposite);
                }                        

                castle_rights[clr] = NO_CASTLING;
                goto finish;
        }        

        //EN PASSANT
        if (mv.is_en_passant()) {
                BB dest = mv.dest();
                int8_t dir = (clr == WHITE) ? -1 : 1;
                pieces[PAWN][clr]   ^= mv.origin() | mv.dest();
                pieces[PAWN][clr^1] ^= shiftBB(dest, 0, dir);
                goto finish;
        }

        //CAPTURE
        if (mv.is_capture()) {
                pieces[mv.their_piece()][clr^1] ^= mv.dest();
        }

        //PROMOTION
        {
                Piece promoted = mv.promoted_piece();
                if (promoted != NO_PIECE) {
                        pieces[PAWN][clr] ^= mv.origin();
                        pieces[promoted][clr] ^= mv.dest();               
                        goto finish;
                }
        }
                
        //NORMAL MOVE
        {
                Piece my_piece = mv.my_piece();
                BB    dest     = mv.dest();
                pieces[my_piece][clr] ^= mv.origin() | dest;
                
                //CHECKING FOR POSITIBILITY OF EN-PASSANT NEXT MOVE
                if (my_piece == PAWN && (
                            (dest & File(3) && clr == WHITE) || 
                            (dest & File(4) && clr == BLACK))) {
                        int8_t dir = (clr == WHITE) ? -1 : 1;
                        en_passant = shiftBB(dest, 0, dir);
                }
        }                        
        
        //SWAPING COLOR AND DISABLING EN PASSANT
finish:
        en_passant = 0;
        clr = (Color) !clr;
}



/*///////////////////////////////////////////////////////////
 *       PRINT FUNCTION USED FOR TESTING, etc.
///////////////////////////////////////////////////////////*/

#include <iostream>

static char find_piece(BB *pieces, BB sq)
{        
        for (int i = WHITE; i != CLR_NB; ++i)
                for (int j = KING; j != PIECE_NB; ++j) {
                        if (pieces[2*j+i] & sq) {
                                char c;
                                switch (j) {
                                case KING : c = 'k'; break;
                                case QUEEN : c = 'q'; break;
                                case BISHOP : c = 'b'; break;
                                case KNIGHT : c = 'n'; break;
                                case ROOK : c = 'r'; break;
                                case PAWN : c = 'p'; break;
                                }                                         
                                if (i == WHITE) 
                                        c -= 32;
                                return c;
                        }
                }
        return ' ';
}

void Board::print()
{
        std::cout << "  " << "o#"[clr == BLACK] << "\n";
        std::cout << "  -----------------\n";
        for (int r = 7; r >= 0; --r){
                std::cout << r+1 << "| ";
                for (int f = 0; f < 8; ++f)
                        std::cout << find_piece((BB*)pieces, 1ULL << (8*r+f)) << " ";
                std::cout << "|\n";
        }
        std::cout << "  -----------------\n";
        std::cout << "   A B C D E F G H\n\n";
}

