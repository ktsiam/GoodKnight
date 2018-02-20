#ifndef TRAVERSER_H_
#define TRAVERSER_H_

#include "evaluator.h"
#include "move_maker.h"

const uint8_t DEPTH = 5;

class Traverser : public Evaluator, public Move_maker {

public:
        Traverser()  = default;
        ~Traverser() = default;

        Move best_move();
        
private:

        // alpha-beta prunning
        Score alphaBetaMax(Score alpha, Score beta, uint8_t depthleft);
        Score alphaBetaMin(Score alpha, Score beta, uint8_t depthleft);
        
        void check_killer_mv(std::vector<Move> &moves, uint8_t depthleft);
        Move killer_moves[DEPTH];
};

#endif // TRAVERSER_H_
