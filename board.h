#ifndef BOARD_H_
#define BOARD_H_

#include "basic.h"
#include "move.h"
#include <vector>
#include <stack>

class Board {
public:
        Board();
        ~Board() = default;
        
        virtual void front_move(const Move mv) = 0;
        virtual void back_move ()              = 0;
        virtual void init_moves()              = 0;
        
        std::vector<Move> move_vec;

protected:

        //position
        BB pieces[CLR_NB][PIECE_NB];
        BB moves [CLR_NB][PIECE_NB];
        
        Color clr;
        Castling castle_rights[CLR_NB];
        BB en_passant_sq;

        //move history
        std::stack<Move> history;
        
private:
        
        //move generators
        void castling_gen();
        void king_move_gen();
        void knight_move_gen();
        void pawn_move_gen();
        void rook_move_gen();
        void bishop_move_gen();
        void queen_move_gen();

        //static generator helpers
        void general_move_gen(BB origin, Piece pce, BB squares);
        void pawn_move       (BB origin, BB dest);
        void pawn_capture    (BB origin, BB dest);        
        void promotion_gen   (BB origin, BB dest, bool quiet);
        BB   rel_shift_up  (BB b, uint8_t shift);
        BB   rel_shift_down(BB b, uint8_t shift);

        //sliding generator helpers
        void rank_move_gen    (BB origin, Piece pce);
        void file_move_gen    (BB origin, Piece pce);
        void diagonal_move_gen(BB origin, Piece pce);
        void antidiag_move_gen(BB origin, Piece pce);
        uint8_t byte_bb_gen      (uint8_t orig, uint8_t occup);
        uint8_t byte_bb_gen_left (uint8_t orig, uint8_t occup);
        uint8_t byte_bb_gen_right(uint8_t orig, uint8_t occup);
};


#endif // BOARD_H_
