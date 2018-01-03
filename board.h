#ifndef BOARD_H_
#define BOARD_H_

#include "basic.h"
#include "move.h"
#include <vector>

class Board {
public:
        Board();
        void front_move(const Move &mv);
        void back_move (const Move &mv);

        void init_moves();
        std::vector<Move> move_vec;

protected:

        Piece find_piece(BB sq, Color c);

        //position
        BB pieces[CLR_NB][PIECE_NB];
        Color clr;
        Castling castle_rights[CLR_NB];
        BB en_passant_sq;

private:

        //temporary variables (re-evaluated each position)
        BB all_pieces;
        BB team_pieces[CLR_NB];

        //move generators
        void castling_gen();
        void king_move_gen();
        void knight_move_gen();
        void pawn_move_gen();

        //TODO: //////////////
        void rook_move_gen(); //U.C.
        void bishop_move_gen();
        void queen_move_gen();
        //////////////////////

        //TODO://///////////HELPER//
        uint8_t byte_bb_gen(uint8_t orig, uint8_t occup);
        void rank_move_gen(BB origin, Piece pce);
        void file_move_gen(BB origin, Piece pce);
        void sliding_move_gen(BB origin, BB dest, Piece pce);
        void edge_move_gen(BB origin, BB dest, Piece pce);

        /////////////////////

        //generator helpers
        void general_move_gen(BB origin, Piece pce, BB moves);
        void en_passant_gen(BB pawns);
        void promotion_gen(BB origin, BB dest, Piece = NO_PIECE);
        void double_move_gen(BB origin);
        void pawn_attack_gen(BB origin);
        void pawn_non_attack_gen(BB origin);

        //move helper
        void castle(Castling cstl, Color c);
        void en_passant(BB org, BB dest, Color c);
        void capture(BB dest, Piece pce, Color c);
        void promote(BB org, BB dest, Piece new_pce, Color c);
        void displace(BB org, BB dest, Piece pce, Color c);
        void set_en_passant(BB org, BB dest);
};


#endif // BOARD_H_
