#include "evaluator.h"

Evaluator::Evaluator()
{
}

int Evaluator::evaluate() 
{
        //TODO
        return                
                900 * pop_count(pieces[clr  ][QUEEN ]) +
                500 * pop_count(pieces[clr  ][ROOK  ]) +
                300 * pop_count(pieces[clr  ][BISHOP]) +
                300 * pop_count(pieces[clr  ][KNIGHT]) +
                100 * pop_count(pieces[clr  ][PAWN  ]) -
                900 * pop_count(pieces[clr^1][QUEEN ]) -
                500 * pop_count(pieces[clr^1][ROOK  ]) -
                300 * pop_count(pieces[clr^1][BISHOP]) -
                300 * pop_count(pieces[clr^1][KNIGHT]) -
                100 * pop_count(pieces[clr^1][PAWN  ]);

}
