#ifndef BOARD_H_
#define BOARD_H_

#include "basic.h"
#include "move.h"
#include <vector>
#include <stack>

extern const uint8_t DEPTH;

class Board {
public:
        Board();
        ~Board() = default;
        
        virtual void front_move(const Move mv) = 0;
        virtual void back_move ()              = 0;
        virtual void init_moves()              = 0;
        virtual int  evaluate()                = 0;
        
        std::vector<Move> move_vec;

protected:

        //position
        BB pieces[CLR_NB][PIECE_NB];
        
        Color clr;
        Castling castle_rights[CLR_NB];
        BB en_passant_sq;

        //move history
        std::stack<Move> history;
};


#endif // BOARD_H_
