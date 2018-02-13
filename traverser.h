#ifndef TRAVERSER_H_
#define TRAVERSER_H_

#include "evaluator.h"
#include "move_maker.h"

class Traverser : public Evaluator, public Move_maker {

public:
        Traverser();
        ~Traverser() = default;

        Move best_move();
        
private:
        
        uint8_t depth;

        int move_eval(Move mv);
        
};

#endif // TRAVERSER_H_
