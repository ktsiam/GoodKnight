#ifndef BOARD_H_
#define BOARD_H_

#include "basic.h"
#include "files_ranks.h"
#include "move.h"

class Board {
public:        
        Board();
        Board(BB ks[], BB qs[], BB rs[], BB bs[], BB ns[], BB ps[], Color c);

        BB    get_kingBB  (Color c);
        BB    get_queenBB (Color c);
        BB    get_rookBB  (Color c);
        BB    get_bishopBB(Color c);
        BB    get_knightBB(Color c);
        BB    get_pawnBB  (Color c);
        Color get_color();

        void  set_kingBB  (BB ks, Color c);
        void  set_queenBB (BB qs, Color c);
        void  set_rookBB  (BB rs, Color c);
        void  set_bishopBB(BB bs, Color c);
        void  set_knightBB(BB ns, Color c);
        void  set_pawnBB  (BB ps, Color c);
        void  set_color(Color c);

private:
        BB k[CLR_NB];
        BB q[CLR_NB];
        BB r[CLR_NB];
        BB b[CLR_NB];
        BB n[CLR_NB];        
        BB p[CLR_NB];
        Color clr;
        Castling castle_rights[CLR_NB];
        BB en_passant;
};


#endif // BOARD_H_
