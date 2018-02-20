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
        int alphaBetaMax( int alpha, int beta, int depthleft);
        int alphaBetaMin( int alpha, int beta, int depthleft);
        
        void check_killer_mv(std::vector<Move> &moves, int depthleft);
        Move killer_moves[DEPTH];
};

#endif // TRAVERSER_H_
