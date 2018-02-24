#include "traverser.h"

#include <climits>
#include <ctime>
#include <cstring>
#include <algorithm>

extern unsigned MOVE_COUNT;
extern unsigned TIME_TAKEN;

Move Traverser::best_move()
{
        clock_t start = clock();
        memset(&killer_moves, 0, sizeof(killer_moves));

        init_moves();
        std::vector<Move> copy = move_vec;
        Score max_score = std::numeric_limits<Score>::min();
        Move best_mv(0);
        
        for (auto it = copy.begin(); it != copy.end(); ++it) {
                
                front_move(*it);
                
                Score score = -alphaBetaMax (std::numeric_limits<Score>::min(),
                                             std::numeric_limits<Score>::max(), DEPTH-1);
                        
                if (score > max_score) {
                        best_mv = *it;
                        max_score = score;
                }
                back_move();
        }

        clock_t end = clock();
        TIME_TAKEN = (end - start);

        return best_mv;
}

Score Traverser::alphaBetaMax(Score alpha, Score beta, uint8_t depthleft)
{
        MOVE_COUNT ++;
        if (depthleft == 0) return evaluate();

        init_moves();

        std::vector<Move> copy = move_vec;
        check_killer_mv(copy, depthleft);
        
        for (auto it = copy.rbegin(); it != copy.rend(); ++it) {
                
                if (!front_move(*it)) return WIN_EVAL + depthleft;
                Score score = alphaBetaMin( alpha, beta, depthleft - 1 );
                back_move();
                
                if(score >= beta) { //killer move
                        killer_moves[depthleft] = *it;
                        return beta;
                }
                if(score > alpha)
                        alpha = score;
        }
        return alpha;
}
                        
Score Traverser::alphaBetaMin(Score alpha, Score beta, uint8_t depthleft)
{
        MOVE_COUNT ++;
        if (depthleft == 0) return -evaluate();

        init_moves();
        
        std::vector<Move> copy = move_vec;
        check_killer_mv(copy, depthleft);
        
        for (auto it = copy.rbegin(); it != copy.rend(); ++it) {
                
                if (!front_move(*it)) return -(WIN_EVAL + depthleft);
                Score score = alphaBetaMax( alpha, beta, depthleft - 1 );
                back_move();
                                
                if( score <= alpha )
                        return alpha;
                if( score < beta )
                        beta = score;
        }
        return beta;
}

void Traverser::check_killer_mv(std::vector<Move> &moves, uint8_t depthleft)
{
        auto killer_mv = std::find(moves.begin(), moves.end(), killer_moves[depthleft]);
        if (killer_mv != moves.end()) {
                moves.erase(killer_mv);
                moves.push_back(*killer_mv);
        }
}
