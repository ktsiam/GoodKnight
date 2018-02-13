#ifndef TRAVERSER_H_
#define TRAVERSER_H_

#include "evaluator.h"
#include "move_maker.h"

class Traverser : public Evaluator, public Move_maker {

public:
        Traverser()  = default;
        ~Traverser() = default;

        Move best_move();
        
private:

        // alpha-beta prunning
        int alphaBetaMax( int alpha, int beta, int depthleft);
        int alphaBetaMin( int alpha, int beta, int depthleft);
        
};

#endif // TRAVERSER_H_
