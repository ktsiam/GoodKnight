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

//TAKE INTO ACCOUNT PROMOTION
void Board::front_move(Move mv)
{
        uint8_t flag = mv.get_flag();
        
        if (flag & 0b110) // castling
                return castle(flag & 0b110);

        Castling cstl = mv.get_castling();
        if (cstl != NO_CASTLING)
                return castle(cstl);      

        Piece myPiece = mv.get_myPiece();
        pieces[myPiece][clr] ^= mv.get_origin() | mv.get_dest();
        
        BB en_p = mv.get_en_passant();
        if (en_p != 0)             
                pieces[P][clr^1] ^= en_p;
        else if (mv.get_theirPiece != 
                pieces[mv.get_theirPiece][clr^1] ^= mv.get_dest();
}

void Board::castle(Castling cstl)
{
        if (cstl == O_O) {
                pieces[K][clr] >>= 2;
                if (clr == WHITE)
                        pieces[R][clr] ^= 0b101 << 5;                
                else 
                        pieces[R][clr] ^= 0b101ULL << 61;                
        }
        else {
                pieces[K][clr] <<= 2;
                if (clr == WHITE)
                        pieces[R][clr] ^= 0b1001;
                else
                        pieces[R][clr] ^= 0b1001ULL << 56;
        }
}















//TO BE IMPLEMENTED IN THE FUTURE:
/*
Board::Board(BB *p[CLR_NB], Color c = WHITE)
{
        for (int p = K; p != PIECE_NB; ++p)
                for (int c = WHITE; c != CLR_NB; ++c)
                        piece[p][c] = p[c];             
   
        clr  = c;
        en_passant = 0;
}
*/
