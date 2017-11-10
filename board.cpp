#include "board.h"

Board::Board()
{
        pieces[0][KING]   = SQ("E1"),          pieces[1][KING]   = SQ("E8");
        pieces[0][QUEEN]  = SQ("D1"),          pieces[1][QUEEN]  = SQ("D8");
        pieces[0][ROOK]   = SQ("A1")|SQ("H1"), pieces[1][ROOK]   = SQ("A8")|SQ("H8");
        pieces[0][BISHOP] = SQ("C1")|SQ("F1"), pieces[1][BISHOP] = SQ("C8")|SQ("F8");
        pieces[0][KNIGHT] = SQ("B1")|SQ("G1"), pieces[1][KNIGHT] = SQ("B8")|SQ("G8");
        pieces[0][PAWN]   = Rank(1),           pieces[1][PAWN]   = Rank(6);

        clr = WHITE;
        en_passant_sq = 0;
}

void Board::front_move(Move mv)
{
        //capture
        if (mv.is_capture())
                capture(mv.dest(), mv.their_piece(), clr);


        //castling
        if (mv.is_castling() != NO_CASTLING) {
                castle(mv.is_castling(), clr);
                castle_rights[clr] = NO_CASTLING;
        }

        //en-passant
        else if (mv.is_en_passant())
                en_passant(mv.origin(), mv.dest(), clr);

        //promotion
        else if (mv.promoted_piece() != NO_PIECE)
                        promote(mv.origin(), mv.dest(), mv.promoted_piece(), clr);

        //displacement
        else {
                displace(mv.origin(), mv.dest(), mv.my_piece(), clr);
                //checking for future en-passant
                if (mv.my_piece() == PAWN)
                        set_en_passant(mv.origin(), mv.dest());
        }

        //swaping color
        clr = (Color) !clr;
}

void Board::back_move(Move mv)
{
        //swapping color
        clr = (Color) !clr;

        //capture
        if (mv.is_capture())
                capture(mv.dest(), mv.their_piece(), clr);


        //castling
        if (mv.is_castling() != NO_CASTLING) {
                castle(mv.is_castling(), clr);
                castle_rights[clr] = mv.castle_rights();
        }

        //en-passant
        else if (mv.is_en_passant())
                en_passant_sq = en_passant(mv.origin(), mv.dest(), clr);

        //promotion
        else if (mv.promoted_piece() != NO_PIECE)
                        promote(mv.origin(), mv.dest(), mv.promoted_piece(), clr);

        //displacement
        else
                displace(mv.origin(), mv.dest(), mv.my_piece(), clr);
}

void Board::castle(Castling cstl, Color c)
{
        uint8_t opposite = (c == BLACK) * 7;
        if (cstl == O_O) {
                pieces[c][KING] ^= shiftBB(0b101, 4, opposite);
                pieces[c][ROOK] ^= shiftBB(0b101, 5, opposite);
        }
        else {
                pieces[c][KING] ^= shiftBB(0b101,  2, opposite);
                pieces[c][ROOK] ^= shiftBB(0b1001, 0, opposite);
        }
}

BB Board::en_passant(BB org, BB dest, Color c)
{
        int8_t dir = (c == WHITE) ? -1 : 1;
        pieces[c][PAWN]   ^= org | dest;
        return pieces[c^1][PAWN] ^= shiftBB(dest, 0, dir);
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
        for (int r = DIM-1; r >= 0; --r){
                std::cout << r+1 << "| ";
                for (int f = 0; f < DIM; ++f)
                        std::cout << find_piece((BB*)pieces, 1ULL << (8*r+f)) << " ";
                std::cout << "|\n";
        }
        std::cout << "  -----------------\n";
        std::cout << "   A B C D E F G H\n\n";
}

