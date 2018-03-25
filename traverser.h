#ifndef TRAVERSER_H_
#define TRAVERSER_H_

#include "evaluator.h"
#include "move_maker.h"


const uint8_t MAX_DEPTH = 5;

class Traverser : public Evaluator, public Move_maker {

public:
        Traverser()  = default;
        ~Traverser() = default;

        void analyze(); // throws if no moves

protected:

        Score best_evaluation;
        Move  best_move;

private:
        
        Score alphaBeta (Score alpha, Score beta, int8_t depthleft);
        Score quiescence(Score alpha, Score beta, int8_t depthleft);
        
        void check_killer_mv(std::vector<Move> &moves, int8_t depthleft);
        std::vector<Move> killer_moves;
};

#endif // TRAVERSER_H_
