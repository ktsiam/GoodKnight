#ifndef EVALUATOR_H_
#define EVALUATOR_H_

#include "move_generator.h"

const Score WIN_EVAL = 20000000;

class Evaluator : public Move_generator {
        
public:
        Evaluator()  = default;
        ~Evaluator() = default;
        Score evaluate() override;
        Score no_move_eval(uint8_t depthleft);        
        
        
/******** INHERITED VARIABLES TO BE USED *****
        BB pieces   [CLR_NB][PIECE_NB];
        BB movement [CLR_NB][PIECE_NB];
        
        Color clr;
        Castling castle_rights[CLR_NB];
        BB en_passant_sq;

        BB all_pieces;
        BB team_pieces[CLR_NB];
        BB team_moves [CLR_NB];
*/
};

#endif // EVALUATOR_H_
