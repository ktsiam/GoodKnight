#include "traverser.h"

#include <limits>
#include <algorithm>

static const uint8_t MAX_QUIENCE = 10; // even

void Traverser::analyze()
{       
        init_moves(false);        
        if (move_vec.empty()) throw "NO_MOVES";
        
        std::vector<Move> move_vec_copy = move_vec;

        Move  best_mv  = Move(0);

        Score alpha = -std::numeric_limits<Score>::max();
        Score beta  =  std::numeric_limits<Score>::max();
        for (auto mv : move_vec_copy) {
                
                front_move(mv);
                Score curr = -alphaBeta(-beta, -alpha, 1);
                back_move();               
                if (curr > alpha) {
                        alpha = curr;
                        best_mv = mv;
                }
        }
        assert(best_mv);

        best_move       = best_mv;
        best_evaluation = alpha;
}

Score Traverser::alphaBeta(Score alpha, Score beta, int8_t depth)
{
        if (!pieces[clr][KING]) return -(WIN_EVAL - depth);
        if (depth == MAX_DEPTH) return  history.top().is_quiet() ?
                                        evaluate() :
                                        quiescence(alpha, beta, depth);
        
        init_moves(false);
        if (move_vec.empty())   return no_move_eval(depth);
        
        std::vector<Move> move_vec_copy = move_vec;

        for (auto mv : move_vec_copy) {
                front_move(mv);
                Score curr = -alphaBeta(-beta, -alpha, depth + 1);
                back_move();
                
                if (curr >= beta) return beta; // beta cutoff
                if (curr > alpha) alpha = curr;
        }
        return alpha;
}

Score Traverser::quiescence(Score alpha, Score beta, int8_t depth) {
        if (!pieces[clr][KING])   return -(WIN_EVAL - depth);
        if (depth == MAX_QUIENCE) return evaluate();
        
        init_moves(false);
        if (move_vec.empty())     return no_move_eval(depth);
        
        Score stand_pat = evaluate();
        if (stand_pat >= beta)
                return beta; // beta cutoff
        if (stand_pat > alpha)
                alpha = stand_pat; // alpha = max

        std::vector<Move> move_vec_copy = move_vec;

        for (auto mv : move_vec_copy) {
                if (mv.is_quiet()) continue;
                
                front_move(mv);
                Score curr = -quiescence(-beta, -alpha, depth + 1);
                back_move();
                if (curr >= beta) return beta; // beta cutoff
                if (curr > alpha) alpha = curr;
        }
        return alpha;
}

/*void Traverser::check_killer_mv(std::vector<Move> &moves, int8_t depth)
{
        auto killer_mv = std::find(moves.begin(), moves.end(), killer_moves[depth]);
        if (killer_mv != moves.end()) {
                moves.erase(killer_mv);
                moves.push_back(*killer_mv);
        }
        }*/
