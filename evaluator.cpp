#include "evaluator.h"

int Evaluator::evaluate()  //NEEDS (A LOT OF) WORK
{        
        return          //material count
                1000000 *    !!(pieces[clr  ][KING  ]) +
                900 * pop_count(pieces[clr  ][QUEEN ]) +
                500 * pop_count(pieces[clr  ][ROOK  ]) +
                300 * pop_count(pieces[clr  ][BISHOP]) +
                300 * pop_count(pieces[clr  ][KNIGHT]) +                        
                100 * pop_count(pieces[clr  ][PAWN  ]) -
                
                1000000 *    !!(pieces[clr^1][KING  ]) -
                900 * pop_count(pieces[clr^1][QUEEN ]) -
                500 * pop_count(pieces[clr^1][ROOK  ]) -
                300 * pop_count(pieces[clr^1][BISHOP]) -
                300 * pop_count(pieces[clr^1][KNIGHT]) -
                100 * pop_count(pieces[clr^1][PAWN  ]);

}
