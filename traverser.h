#ifndef TRAVERSER_H_
#define TRAVERSER_H_

#include "evaluator.h"
#include "move_maker.h"


const uint8_t DEPTH = 5;

class Traverser : public Evaluator, public Move_maker {

public:
        Traverser()  = default;
        ~Traverser() = default;

        Line analyze(); // throws if no moves

protected:
        
        Line main_line;
        
private:

        Line alphaBeta(Score alpha, Score beta, uint8_t depthleft);
        
        void check_killer_mv(std::vector<Move> &moves, uint8_t depthleft);
        std::vector<Move> killer_moves;
};

#endif // TRAVERSER_H_
