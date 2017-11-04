#ifndef BOARD_H_
#define BOARD_H_

#include "basic.h"
#include "files_ranks.h"
#include "move.h"
#include <vector>

class Board {
public:
        Board();
        Board(BB ks[], BB qs[], BB rs[], BB bs[], BB ns[], BB ps[], Color c);

protected:
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
