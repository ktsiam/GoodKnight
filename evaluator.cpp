#include "evaluator.h"

Score Evaluator::evaluate()  //NEEDS (A LOT OF) WORK
{
        only_movement[clr] = true;
        init_moves();
        only_movement[clr] = false;

        BB central_pawns_w = pieces[clr  ][PAWN] & 0x1c1c000000;
        BB central_pawns_b = pieces[clr^1][PAWN] & 0x1c1c000000;
        
        return          //material count
                900 * pop_count(pieces[clr  ][QUEEN ]) +
                500 * pop_count(pieces[clr  ][ROOK  ]) +
                300 * pop_count(pieces[clr  ][BISHOP]) +
                300 * pop_count(pieces[clr  ][KNIGHT]) +                        
                100 * pop_count(pieces[clr  ][PAWN  ]) +
                20  * pop_count(central_pawns_w)       -
                
                900 * pop_count(pieces[clr^1][QUEEN ]) -
                500 * pop_count(pieces[clr^1][ROOK  ]) -
                300 * pop_count(pieces[clr^1][BISHOP]) -
                300 * pop_count(pieces[clr^1][KNIGHT]) -
                100 * pop_count(pieces[clr^1][PAWN  ]) -
                20  * pop_count(central_pawns_b);

}

Score Evaluator::no_move_eval(uint8_t depthleft)
{
        only_movement[clr] = true;
        init_moves();
        only_movement[clr] = false;
        return (pieces[clr][KING] & team_movement[clr^1]) ?
                -(WIN_EVAL + depthleft) : 0;
}
