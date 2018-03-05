#include "traverser.h"

#include <climits>
#include <algorithm>

static const uint8_t MAX_QUIENCE = 10; // even

Line Traverser::analyze()
{
        killer_moves = main_line.seq;
        std::reverse(killer_moves.begin(), killer_moves.end());
        killer_moves.resize(MAX_QUIENCE);
        
        init_moves(false);
        if (move_vec.empty()) throw "NO_MOVES";
        
        main_line = alphaBeta ( Line { -(WIN_EVAL - MAX_DEPTH), {} },
                                Line {   WIN_EVAL - MAX_DEPTH , {} }, 0);

        return main_line;
}

Line Traverser::alphaBeta(Line alpha, Line beta, int8_t depth)
{
        if (!pieces[clr][KING]) return Line{ -(WIN_EVAL - depth), {} };
        if (depth == MAX_DEPTH)
                return (history.top().is_quiet()) ?
                        Line{ evaluate(), {} }       :
                        Line{ evaluate(), {} };
                        //-quiescence(-beta, -alpha, depth + 1));
        
        init_moves(false);
        if (move_vec.empty())   return Line{ no_move_eval(depth), {} };
        
        auto copy = move_vec;
        check_killer_mv(copy, depth);
        
        for (auto it = copy.rbegin(); it != copy.rend(); ++it) {
                front_move(*it);
                Line curr = -alphaBeta(-beta, -alpha, depth + 1);
                back_move();
                if (curr >= beta) {
                        killer_moves[depth] = beta.seq.back();
                        return beta; // beta cutoff
                }
                if (curr > alpha)
                        alpha = cons(*it, curr); // alpha = max
        }        
        return alpha;
}

Line Traverser::quiescence(Line alpha, Line beta, int8_t depth) {
        if (!pieces[clr][KING])       return Line{ -(WIN_EVAL - depth), {} };
        if (depth == MAX_QUIENCE) return Line{ evaluate()         , {} };
        init_moves(false);
        if (move_vec.empty())         return Line{ no_move_eval(depth), {} };
                
        Line stand_pat = Line{ evaluate(), {} };        
        if(stand_pat >= beta)
                return beta; // beta cutoff
        if(stand_pat > alpha)
                alpha = stand_pat; // alpha = max

        auto copy = move_vec;
        check_killer_mv(copy, depth);

        for (auto it = copy.rbegin(); it != copy.rend(); ++it) {
                if (it -> is_quiet()) continue;
                front_move(*it);
                Line curr = -quiescence(-beta, -alpha, depth + 1);
                back_move();
                if (curr >= beta) {
                        killer_moves[depth] = beta.seq.back();
                        return beta; // beta cutoff
                }
                if (curr > alpha)
                        alpha = cons(*it, curr); // alpha = max
        }
        return alpha;
}

void Traverser::check_killer_mv(std::vector<Move> &moves, int8_t depth)
{
        auto killer_mv = std::find(moves.begin(), moves.end(), killer_moves[depth]);
        if (killer_mv != moves.end()) {
                moves.erase(killer_mv);
                moves.push_back(*killer_mv);
        }
}
