#ifndef MOVE_GENERATOR_
#define MOVE_GENERATOR_

#include "board.h"

class Move_generator : virtual public Board{
        
public:
        Move_generator();
        ~Move_generator() = default;

        void init_moves(bool quick) override;

protected:
        //re-evaluated each run
        BB all_pieces;
        BB team_pieces[CLR_NB];
        BB team_movement [CLR_NB];
        BB movement[CLR_NB][PIECE_NB];
        bool only_movement[CLR_NB];

        //useful helper
        Piece find_piece(BB sq, Color c);
private:

        //prevents illegal king moves
        void init_opp_movement(bool quick);

        //move generators
        void king_move_gen();
        void knight_move_gen();
        void pawn_move_gen();
        void rook_move_gen();
        void bishop_move_gen();
        void queen_move_gen();
        void castling_gen();

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

#endif // MOVE_GENERATOR_
