#include "board.h"

#include "move_table.h"

/**************************
 * BB KNIGHT_MOVE   [64]  *
 * BB KING_MOVE     [64]  *
 * BB PAWN_ATTACK[2][64]  *
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
        pawn_move_gen();
        rook_move_gen();
}

Piece Board::find_piece(BB sq, Color c)
{
        if (!(team_pieces[c] & sq))
                return NO_PIECE;
        for (int i = KING; i != PIECE_NB; ++i)
                if (pieces[c][i] & sq)
                        return (Piece) i;
        assert(false);
}

void Board::castling_gen() // FIX WHEN CASTLING POSITION IS ATTACKED
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
                move_vec.push_back(Move{origin, dest, pce, castle_rights[clr], en_passant_sq});
        }

        while (attack) {
                BB dest     = get_clear_lsb(attack);
                Piece their = find_piece(dest, (Color) (clr^1));
                Move new_mv{origin, dest, pce, castle_rights[clr], en_passant_sq, their};
                move_vec.push_back(new_mv);
        }
}

void Board::pawn_move_gen()
{
        BB pawn_pos = pieces[clr][PAWN];
        BB en_p_rank = Rank((clr == WHITE) ? 4 : 3);

        if (en_passant_sq && (pawn_pos & en_p_rank))
                en_passant_gen(pawn_pos & en_p_rank);

        while (pawn_pos) {
                BB origin = get_clear_lsb(pawn_pos);

                pawn_attack_gen    (origin);
                pawn_non_attack_gen(origin);
        }
}

void Board::pawn_non_attack_gen(BB origin)
{
        int8_t push = (clr == WHITE) ? 1 : -1;
        BB     dest = shiftBB(origin, 0, push);

        if ( ~(all_pieces) & dest) {
                BB promo_rank = Rank((clr == WHITE) ? 7 : 0);
                if (dest & promo_rank)
                        promotion_gen(origin, dest, NO_PIECE);
                else {
                        Move new_mv{origin, dest, PAWN, castle_rights[clr], en_passant_sq};
                        move_vec.push_back(new_mv);

                        BB double_move_rank = Rank((clr == WHITE) ? 2 : 5);
                        if (dest & double_move_rank)
                                double_move_gen(origin);
                }
        }
}

void Board::pawn_attack_gen(BB origin)
{
        BB attack = PAWN_ATTACK[clr][get_idx(origin)];
        while (attack) {
                BB dest     = get_clear_lsb(attack);

                if (dest & ~team_pieces[clr^1])
                        continue;

                Piece their = find_piece(dest, (Color) (clr^1));
                BB promo_rank = Rank((clr == WHITE) ? 7 : 0);
                if (dest & promo_rank)
                        promotion_gen(origin, dest, their);
                else {
                        Move new_mv{origin, dest, PAWN, castle_rights[clr], en_passant_sq, their};
                        move_vec.push_back(new_mv);
                }
        }
}


void Board::en_passant_gen(BB pawns)
{
        while (pawns) {
                BB origin = get_clear_lsb(pawns);
                BB dest   = PAWN_ATTACK[clr][get_idx(origin)] & en_passant_sq;
                if (dest) {

                        //en passant is NOT a capture
                        Move new_mv{origin, dest, PAWN, castle_rights[clr], en_passant_sq,
                                        NO_PIECE, NO_CASTLING, NO_PIECE, true};
                        move_vec.push_back(new_mv);
                }
        }
}

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
        BB dest = shiftBB(origin, 0, clr==WHITE ? 2 : -2);

        if (~all_pieces & dest) {
                Move new_mv{origin, dest, PAWN, castle_rights[clr], en_passant_sq};
                move_vec.push_back(new_mv);
        }
}

void Board::rook_move_gen()
{
        BB rooks = pieces[clr][ROOK];
        while (rooks) {
                BB origin = get_clear_lsb(rooks);
                rank_move_gen(origin, ROOK);
                //file_move_gen(origin, ROOK);///////////FIXXIXIXIXIXIIXIXI
        }
}

uint8_t Board::byte_bb_gen(uint8_t orig, uint8_t occup)
{
        uint8_t dest = ((occup - 2 * orig) ^ occup);

        uint8_t occup_r  = rev_bits(occup);
        uint8_t origin_r = rev_bits(orig);
        
        dest |= rev_bits(((occup_r - 2 * origin_r) ^ occup_r));
        return dest;        
}

void Board::rank_move_gen(BB origin, Piece pce)
{
        uint8_t shift = get_idx(origin) / DIM * DIM;

        BB dest = byte_bb_gen(origin >> shift, all_pieces >> shift);
        sliding_move_gen(origin, dest << shift, pce);
}

void Board::sliding_move_gen(BB origin, BB dest, Piece pce)
{       
        edge_move_gen(origin, get_clear_lsb(dest), pce);
        edge_move_gen(origin, get_clear_msb(dest), pce);
        
        while (dest) {
                BB d = get_clear_lsb(dest);
                Move new_mv{origin, d, pce, castle_rights[clr],
                en_passant_sq, find_piece(dest, static_cast<Color>(clr^1))};
                move_vec.push_back(new_mv);
        }
}

void Board::edge_move_gen(BB origin, BB dest, Piece pce)
{
        if (dest & team_pieces[clr^1]) { //capture
                Move new_mv{origin, dest, pce, castle_rights[clr],
                en_passant_sq, find_piece(dest, static_cast<Color>(clr^1))};
                move_vec.push_back(new_mv);
        }
        else if (dest & ~all_pieces) {   //free square
                Move new_mv{origin, dest, pce, castle_rights[clr],
                en_passant_sq};
                move_vec.push_back(new_mv);
        }
}

