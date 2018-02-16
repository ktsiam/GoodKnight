#ifndef STATE_H_
#define STATE_H_

#include "basic.h"

struct State {
        BB pieces[CLR_NB][PIECE_NB];        
        Color clr;
        Castling castle_rights[CLR_NB];
        BB en_passant_sq;
};


#endif // STATE_H_
