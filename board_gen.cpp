#include "board.h"

#include "move_table.h"

/**************************
 * BB KNIGHT_MOVE   [64]  *
 * BB KING_MOVE     [64]  *
 * BB PAWN_ATTACK[2][64]  *
 * BB PAWN_MOVE  [2][64]  *
 **************************/

void Board::init_moves()
{
        team_pieces[WHITE] = unite(&pieces[WHITE][KING], &pieces[WHITE][PIECE_NB]);
        team_pieces[BLACK] = unite(&pieces[BLACK][KING], &pieces[BLACK][PIECE_NB]);

        all_pieces = team_pieces[WHITE] | team_pieces[BLACK];

        move_vec.clear();

        castling_gen();
        king_move_gen();
        knight_move_gen();

        //no pawns yet!
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
        int8_t y_shift = clr * 7;
        if (castle_rights[clr] & 1)
                if ((~shiftBB(0b11, 5, y_shift) & all_pieces) == all_pieces)
                        move_vec.push_back(Move(0, 0, NO_PIECE, castle_rights[clr],
                                                en_passant_sq, NO_PIECE, O_O));
        if (castle_rights[clr] & 2)
                if ((~shiftBB(0b111, 1, y_shift) & all_pieces) == all_pieces)
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
                BB moves  = KNIGHT_MOVE[get_idx(origin)];

                general_move_gen(origin, KNIGHT, moves);
        }
}



void Board::general_move_gen(BB origin, Piece pce, BB moves)
{       
        moves &= ~team_pieces[clr];

        if (!moves) return;

        BB attack     = moves & team_pieces[clr^1];
        BB non_attack = moves ^ attack;        

        while (non_attack) {
                BB dest = get_clear_lsb(non_attack);      
                move_vec.push_back(Move{origin, dest, pce, castle_rights[clr], 0});
        }

        while (attack) {
                BB dest     = get_clear_lsb(attack);
                Piece their = find_piece(dest, (Color) (clr^1));
                Move new_mv{origin, dest, pce, castle_rights[clr], 0, their};
                move_vec.push_back(new_mv);
        }        
}


////////////////////////////////////////////////////////
//////////////////NEEEEDDDSSS WORRRRK///////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////


void Board::pawn_white_move_gen()
{
/*
        BB pawn_pos = pieces[WHITE][PAWN];

        //check for en_passant
        if (en_passant_sq && (pawn_pos & Rank(4)))
                en_passant_gen(pawn_pos & Rank(4));

        //go 1-by-1 pawns
        while (pawn_pos) {

                BB origin = get_clear_lsb(pawn_pos);
                BB attack = PAWN_ATTACK[WHITE][get_idx(origin)];
                
                //find 1-by-1 attacks
                while (attack) {
                        BB dest     = get_clear_lsb(attack);
                        Piece their = find_piece(dest, (Color) (clr^1));

                        //check for promotion
                        if (dest & Rank(7))
                                promotion_gen(origin, dest, their);
                        //add normal attack move
                        else {                        
                                Move new_mv{origin, dest, PAWN, castle_rights[clr], en_passant_sq, their};
                                move_vec.push_back(new_mv);
                        }
                }

                //find non-attacks
                BB dest = shiftBB(origin, 1, 0);
                
                //if front move possible
                if ( ~(all_pieces) & dest) {

                        //check for promotion
                        if (dest & Rank(7))
                                promotion_gen(origin, dest, NO_PIECE);

                        //add normal non-attack move
                        else {
                                Move new_mv{origin, dest, PAWN, castle_rights[clr], en_passant_sq};
                                move_vec.push_back(new_mv);

                                //if potential double-move
                                if (dest & Rank(2))                                         
                                        double_move_gen(origin);                                                                
                        }
                }
        }                
*/
}

void Board::en_passant_gen(BB pawns)
{
        while (pawns) {
                BB origin = get_clear_lsb(pawns);
                BB dest   = PAWN_ATTACK[WHITE][get_idx(origin)];
                if (dest & en_passant_sq) {

                        //en passant is NOT a capture
                        Move new_mv{origin, dest, PAWN, castle_rights[clr], en_passant_sq, 
                                        NO_PIECE, NO_CASTLING, NO_PIECE, true};
                        move_vec.push_back(new_mv);                        
                }
        }
}

void Board::pawn_black_move_gen(){  }

void Board::promotion_gen(BB origin, BB dest, Piece their)
{
        for (int p = QUEEN; p != PAWN; ++p) {
                Move new_mv{ origin, dest, PAWN, castle_rights[clr], 
                             en_passant_sq, their, NO_CASTLING, (Piece) p };
                move_vec.push_back(new_mv);
        }
}

void Board::double_move_gen(BB origin)
{
        BB dest = shiftBB(origin, 0, 2);
                
        if (~all_pieces & dest) {
                Move new_mv{origin, dest, PAWN, castle_rights[clr], en_passant_sq};
                move_vec.push_back(new_mv);
        }
}
