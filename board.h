#ifndef BOARD_H_
#define BOARD_H_

#include "basic.h"
#include "move.h"
#include "state.h"

#include <vector>
#include <stack>

class Board : protected State {
public:
        Board();
        ~Board() = default;
        
        virtual bool  front_move(const Move mv) = 0;
        virtual void  back_move ()              = 0;
        virtual void  init_moves(bool quick)    = 0;
        virtual Score evaluate()                = 0;
        
        std::vector<Move> move_vec;

protected:

        std::stack<Move> history;
};


#endif // BOARD_H_
