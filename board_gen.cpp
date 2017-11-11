#include "board.h"

#include "move_table.h"

/**************************
 * BB KNIGHT_MOVE   [64]  *
 * BB KING_MOVE     [64]  *
 * BB PAWN_ATTACK[2][64]  *
 * BB PAWN_MOVE  [2][64]  *
 **************************/

void Board::init_variables()
{
        all_pieces[WHITE] = unite(&pieces[WHITE][KING], &pieces[WHITE][PIECE_NB]);
        all_pieces[BLACK] = unite(&pieces[BLACK][KING], &pieces[BLACK][PIECE_NB]);
}

Piece Board::find_piece(BB sq, Color c)
{
        for (int i = KING; i != PIECE_NB; ++i)
                if (pieces[c][i] & sq)
                        return (Piece) i;
        return NO_PIECE;
}

void Board::castling_gen()
{
        if (castle_rights[clr] & 1)
                move_vec.push_back(Move(0, 0, NO_PIECE, castle_rights[clr],
                                        en_passant_sq, NO_PIECE, O_O));
        if (castle_rights[clr] & 2)
                move_vec.push_back(Move(0, 0, NO_PIECE, castle_rights[clr],
                                        en_passant_sq, NO_PIECE, O_O_O));
}

void Board::king_move_gen()
{       
        BB origin = pieces[clr][KING];
        BB moves  = KING_MOVE[get_idx(origin)];
        general_move_gen(origin, KING, moves);        
}

void Board::knight_move_gen()
{
        BB knight_pos = pieces[clr][KNIGHT];
        
        while (knight_pos) {
                BB origin = get_clear_lsb(knight_pos);
                general_move_gen(origin, KNIGHT, KNIGHT_MOVE[origin]);
        }
}

void Board::general_move_gen(BB origin, Piece pce, BB moves)
{       
        
        if (!moves) return;

        BB attack     = moves & ~all_pieces[clr^1];
        BB non_attack = moves ^ attack;

        while (non_attack) {
                BB dest = get_clear_lsb(moves);      
                move_vec.push_back(Move{origin, dest, pce, castle_rights[clr], 0});
        }

        while (attack) {
                BB dest     = get_clear_lsb(moves);
                Piece their = find_piece(dest, (Color) (clr^1));
                move_vec.push_back(Move{origin, dest, pce, castle_rights[clr], 0, their});
        }        
}



