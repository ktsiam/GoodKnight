#include "traverser.h"

#include <climits>
#include <ctime>

extern unsigned MOVE_COUNT;
extern unsigned TIME_TAKEN;

Move Traverser::best_move()
{

        clock_t start = clock();
        
        init_moves();
        std::vector<Move> copy = move_vec;
        int max_score = std::numeric_limits<int>::min();
        Move best_mv; //initialized to 0

        
        for (auto it = copy.begin(); it != copy.end(); ++it) {

                front_move(*it);
                
                int score = -alphaBetaMax (std::numeric_limits<int>::min(),
                                           std::numeric_limits<int>::max(), DEPTH-1);
                        
                if (score > max_score) {
                        best_mv = *it;
                        max_score = score;
                }
                back_move();
        }

        clock_t end = clock();
        TIME_TAKEN = (end - start);

        assert((uint32_t)best_mv);
        return best_mv;
}

int Traverser::alphaBetaMax(int alpha, int beta, int depthleft)
{
        MOVE_COUNT ++;
        if ( depthleft == 0 ) return evaluate();

        init_moves();
        std::vector<Move> copy = move_vec;
        for (auto it = copy.begin(); it != copy.end(); ++it) {
                
                front_move(*it);                
                int score = alphaBetaMin( alpha, beta, depthleft - 1 );
                back_move();
                
                if( score >= beta )
                        return beta;
                if( score > alpha )
                        alpha = score;
        }
        return alpha;
}
 
int Traverser::alphaBetaMin(int alpha, int beta, int depthleft)
{
        MOVE_COUNT ++;
        if ( depthleft == 0 ) return -evaluate();

        init_moves();
        std::vector<Move> copy = move_vec;
        for (auto it = copy.begin(); it != copy.end(); ++it) {

                front_move(*it);                
                int score = alphaBetaMax( alpha, beta, depthleft - 1 );
                back_move();
                                
                if( score <= alpha )
                        return alpha;
                if( score < beta )
                        beta = score;
        }
        return beta;
}
