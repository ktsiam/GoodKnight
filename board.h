#ifndef BOARD_H_
#define BOARD_H_

#include "basic.h"
#include "files_ranks.h"

struct Board {
        BB k[CLR_NB];
        BB q[CLR_NB];
        BB r[CLR_NB];
        BB b[CLR_NB];
        BB n[CLR_NB];        
        BB p[CLR_NB];
        Color clr;
};

const Board BOARD_INIT { 
        {E1, E8}, {D1, D8}, {A1|A8, H1|H8}, 
        {C1|F1, C8|F8}, {B1|G1, B8|G8}, {Rank(1), Rank(6)}, WHITE 
};

//ADD FEN READ FUNCTION

#endif // BOARD_H_
