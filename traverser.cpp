#include "traverser.h"

#include <climits>
#include <algorithm>

static const uint8_t MAX_QUIENCE = 20;

Line Traverser::analyze()
{
        killer_moves = main_line.seq;
        killer_moves.resize(MAX_QUIENCE);
        
        init_moves();
        if (move_vec.empty()) throw "NO_MOVES";
        
        main_line = alphaBeta ( -(WIN_EVAL + DEPTH), WIN_EVAL + DEPTH, DEPTH);

        return main_line;
}

Line Traverser::alphaBeta(Score alpha, Score beta, uint8_t depthleft)
{
        if (!pieces[clr][KING]) return Line{ -(WIN_EVAL + depthleft), {} };
        if (depthleft == 0)     return Line{ evaluate()             , {} };        
        init_moves();
        if (move_vec.empty())   return Line{ no_move_eval(depthleft), {} };
        
        auto copy = move_vec;
        check_killer_mv(copy, depthleft);
        
        Line best_ln { -(WIN_EVAL + DEPTH), {} };
        for (auto it = copy.rbegin(); it != copy.rend(); ++it) {
                front_move(*it);
                Line curr = -alphaBeta(-beta, -alpha, depthleft - 1);
                back_move();
                if (curr >= beta) {
                        killer_moves[depthleft] = *it;
                        curr.value = beta;
                        return cons(*it, curr); // beta-cutoff
                }
                if (curr > alpha) {
                        best_ln = cons(*it, curr); // alpha = max
                        alpha   = best_ln.value;
                }
        }        
        return best_ln;
}

void Traverser::check_killer_mv(std::vector<Move> &moves, uint8_t depthleft)
{
        auto killer_mv = std::find(moves.begin(), moves.end(), killer_moves[depthleft]);
        if (killer_mv != moves.end()) {
                moves.erase(killer_mv);
                moves.push_back(*killer_mv);
        }
}
