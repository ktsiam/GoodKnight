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

void Board::pawn_white_move_gen()
{
        BB pawn_pos = pieces[WHITE][PAWN];
        if ((pawn_pos & File(4)) && en_passant_sq)
                en_passant_gen(pawn_pos & File(4));
        
        while (pawn_pos) {
                BB origin = get_clear_lsb(pawn_pos);
                BB attack = PAWN_ATTACK[WHITE][get_idx(origin)];
                
                while (attack) {
                        BB dest     = get_clear_lsb(attack);
                        Piece their = find_piece(dest, (Color) (clr^1));

                        if (dest & File(7))
                                promotion_gen(origin, dest, their);
                        
                        Move new_mv{origin, dest, PAWN, castle_rights[clr], en_passant_sq, their};
                        move_vec.push_back(new_mv);
                }
                BB dest = shiftBB(origin, 1, 0);
                if (~(all_pieces[WHITE] | all_pieces[BLACK]) & dest) {
                        if (dest & File(7))
                                promotion_gen(origin, dest, NO_PIECE);
                        else {
                                Move new_mv{origin, dest, PAWN, castle_rights[clr], en_passant_sq};
                                move_vec.push_back(new_mv);
                                BB dest2 = shiftBB(dest, 0, 1);
                                if (~(all_pieces[WHITE] | all_pieces[BLACK]) & dest2) {
                                        Move new_mv{origin, dest2, PAWN, castle_rights[clr], en_passant_sq};
                                        move_vec.push_back(new_mv);
                                }
                        }
                }                
        }
}

void Board::en_passant_gen(BB pawns)
{
        while (pawns) {
                BB origin = get_clear_lsb(pawns);
                BB dest   = PAWN_ATTACK[WHITE][get_idx(origin)];
                if (dest & en_passant_sq) {
                        //en passant is NOT a capture
                        Move new_mv{origin, dest, PAWN, castle_rights[clr], en_passant_sq, NO_PIECE, NO_CASTLING, NO_PIECE, true};
                        move_vec.push_back(new_mv);
                        
                }
        }
}

void Board::pawn_black_move_gen(){  }

void Board::promotion_gen(BB origin, BB dest, Piece their)
{
        for (int p = QUEEN; p != PAWN; ++p) {
                Move new_mv{ origin, dest, PAWN, castle_rights[clr], 0, 
                                their, NO_CASTLING, (Piece) p };
                move_vec.push_back(new_mv);
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
                Move new_mv{origin, dest, pce, castle_rights[clr], 0, their};
                move_vec.push_back(new_mv);
        }        
}



