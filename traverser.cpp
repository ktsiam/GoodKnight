#include "traverser.h"

#include <climits>

extern unsigned MOVE_COUNT;

Traverser::Traverser()
{        
        depth = 0;
}

#include <iostream>
Move Traverser::best_move()
{
        MOVE_COUNT = 0;
        init_moves();
        
        if (move_vec.empty()) {                
                assert (0 && "STALEMATE");
        }

        std::vector<Move> move_copy = move_vec;
        
        Move best      = move_copy.front();
        int  best_eval = -move_eval(best);
        
        for (auto it = move_copy.begin() + 1; it != move_copy.end(); ++it) {
                int curr_eval = -move_eval(*it);
                if (curr_eval > best_eval) {
                        best_eval = curr_eval;
                        best = *it;
                }
        }
        
        std::cout << "EVALUTATION FOR BLACK: " << best_eval << std::endl;
        return best;
}

int Traverser::move_eval(Move mv)
{
        ++ MOVE_COUNT;
        
        ++ depth;
        front_move(mv);
        init_moves();
        
        int best_eval = std::numeric_limits<int>::min();
        if (depth == DEPTH || mv.their_piece() == KING) {
                best_eval = evaluate();
        } else {               
                std::vector<Move> move_copy = move_vec;
                best_eval = move_eval(move_vec.front());
                for (auto it = move_copy.begin() + 1; it != move_copy.end(); ++it) {
                        int curr_eval = -move_eval(*it);
                        best_eval = std::max(best_eval, curr_eval);
                }
        }
                
        back_move();
        -- depth;

        return best_eval;
}


