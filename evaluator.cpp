#include "evaluator.h"

Score Evaluator::evaluate()
{
        init_moves(true); //quick

        Score eval = material(WHITE) - material(BLACK);
        eval      += position(WHITE) - position(BLACK);

        return (clr == WHITE) ? eval : -eval;
}

Score Evaluator::material(Color c)
{
        return  900 * pop_count(pieces[c][QUEEN ]) +
                500 * pop_count(pieces[c][ROOK  ]) +
                325 * pop_count(pieces[c][BISHOP]) +
                300 * pop_count(pieces[c][KNIGHT]) +
                100 * pop_count(pieces[c][PAWN  ]);
}

Score Evaluator::position(Color c)
{
        Score eval = 0;
        
        BB central_pawns = pieces[c][PAWN] & 0x1c1c000000;
        eval += 20 * pop_count(central_pawns);        

        // isolated pawns
        // double pawns
        // knights in center
        // holes
        // castling rights & king in corner
        // x-rays
        // pawn forward (linear)
        // bishop and light-dark squares
        // bishop pair
        
        return eval;
}


Score Evaluator::no_move_eval(uint8_t depthleft)
{
        init_moves(true); //quick
        
        return (pieces[clr][KING] & team_movement[clr^1]) ?
                -(WIN_EVAL + depthleft) : 0;
}
