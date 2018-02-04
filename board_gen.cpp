#include "board.h"


#include "move_table.h"
/**************************
 * BB KNIGHT_MOVE   [64]  *
 * BB KING_MOVE     [64]  *
 **************************/

////////////////////////////// PUBLIC /////////////////////////////

// HEAD GENERATE FUNCTION

void Board::init_moves()
{
        team_pieces[WHITE] = unite(&pieces[WHITE][KING], &pieces[WHITE][PIECE_NB]);
        team_pieces[BLACK] = unite(&pieces[BLACK][KING], &pieces[BLACK][PIECE_NB]);

        team_moves [WHITE] = unite(&moves[WHITE][KING],  &moves[WHITE][PIECE_NB]);
        team_moves [BLACK] = unite(&moves[BLACK][KING],  &moves[BLACK][PIECE_NB]);
        
        all_pieces = team_pieces[WHITE] | team_pieces[BLACK];

        move_vec.clear();

        castling_gen();
        king_move_gen();
        knight_move_gen();
        pawn_move_gen();
        rook_move_gen();
        bishop_move_gen();
        queen_move_gen();
}

////////////////////////////// PROTECTED /////////////////////////////

Piece Board::find_piece(BB sq, Color c)
{
        if (!(team_pieces[c] & sq))
                return NO_PIECE;
        for (int i = KING; i != PIECE_NB; ++i)
                if (pieces[c][i] & sq)
                        return (Piece) i;
        assert(false);
}

////////////////////////////// PRIVATE /////////////////////////////

// MOVE GENERATING FUNCTIONS (per piece + castling)

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

void Board::pawn_move_gen()
{
        BB pawn_pos = pieces[clr][PAWN];
        
        BB front_1 = rel_shift_up(pawn_pos, DIM) & ~all_pieces;
        BB front_2 = rel_shift_up(front_1,  DIM) & ~all_pieces
                & Rank(clr == WHITE ? 3 : 4);
        
        BB take_left = rel_shift_up(pawn_pos, DIM-1)
                & (team_pieces[clr^1] | en_passant_sq) & ~File(7);
        
        BB take_right = rel_shift_up(pawn_pos, DIM+1)
                & (team_pieces[clr^1] | en_passant_sq) & ~File(0);

        moves[clr][PAWN] = front_1 | front_2 | take_left | take_right;
        
        while (front_1) {
                BB dest = get_clear_lsb(front_1);
                BB orig = rel_shift_down(dest, DIM);
                pawn_move(orig, dest);
        }
        while (front_2) {
                BB dest = get_clear_lsb(front_2);
                BB orig = rel_shift_down(dest, 2*DIM);
                pawn_move(orig, dest);
        }
        while (take_left) {
                BB dest = get_clear_lsb(take_left);
                BB orig = rel_shift_down(dest, DIM-1);
                pawn_capture(orig, dest);
        }
        while (take_right) {
                BB dest = get_clear_lsb(take_right);
                BB orig = rel_shift_down(dest, DIM+1);
                pawn_capture(orig, dest);
        }
}

void Board::rook_move_gen()
{
        BB rooks = pieces[clr][ROOK];
        while (rooks) {
                BB origin = get_clear_lsb(rooks);
                rank_move_gen(origin, ROOK);
                file_move_gen(origin, ROOK);
        }
}

void Board::bishop_move_gen()
{
        BB bishops = pieces[clr][BISHOP];
        while (bishops) {
                BB origin = get_clear_lsb(bishops);
                diagonal_move_gen(origin, BISHOP);
                antidiag_move_gen(origin, BISHOP);
        }
}

void Board::queen_move_gen()
{
        BB queens = pieces[clr][QUEEN];
        while (queens) {
                BB origin = get_clear_lsb(queens);
                rank_move_gen     (origin, QUEEN);
                file_move_gen    (origin, QUEEN);
                diagonal_move_gen(origin, QUEEN);
                antidiag_move_gen(origin, QUEEN);
        }
}



// HELPERS FOR GENERATING FUNCTIONS OF STATIC MOVES

void Board::general_move_gen(BB origin, Piece pce, BB squares)
{
        squares &= ~team_pieces[clr];
        moves[clr][pce] = squares;
        
        if (!squares) return;

        BB attack     = squares & team_pieces[clr^1];
        BB non_attack = squares ^ attack;
        
        while (non_attack) {
                BB dest = get_clear_lsb(non_attack);
                Move new_mv{origin, dest, pce, castle_rights[clr], en_passant_sq};
                move_vec.push_back(new_mv);
        }

        while (attack) {
                BB dest     = get_clear_lsb(attack);
                Piece their = find_piece(dest, (Color) (clr^1));
                Move new_mv{origin, dest, pce, castle_rights[clr],
                                en_passant_sq, their};
                move_vec.push_back(new_mv);
        }
}

void Board::pawn_move(BB origin, BB dest)
{
        if (UNLIKELY(!rel_shift_up(dest, DIM))) {
                promotion_gen(origin, dest,  false);
                return;
        }
        Move new_mv{origin, dest, PAWN, castle_rights[clr], en_passant_sq};
        move_vec.push_back(new_mv);        
}

void Board::pawn_capture(BB origin, BB dest)
{
        //checking for promotion
        if (UNLIKELY(!rel_shift_up(dest, DIM))) {
                promotion_gen(origin, dest,  false);
                return;
        }        
        Piece taken_pce = find_piece(dest, static_cast<Color>(clr^1));
        bool en_p       = (taken_pce == NO_PIECE);
        
        Move new_mv{origin, dest, PAWN, castle_rights[clr],
                en_passant_sq, taken_pce, NO_CASTLING, NO_PIECE, en_p};
        move_vec.push_back(new_mv);        
}

void Board::promotion_gen(BB origin, BB dest, bool quiet)
{
        Piece their = (quiet) ? NO_PIECE :
                find_piece(dest, static_cast<Color>(clr^1));;
        
        for (int p = QUEEN; p != PAWN; ++p) {
                Move new_mv{ origin, dest, PAWN, castle_rights[clr],
                             en_passant_sq, their, NO_CASTLING, (Piece) p };
                move_vec.push_back(new_mv);
        }
}
                                  
BB Board::rel_shift_up(BB b, uint8_t shift)
{
        return (clr == WHITE) ? (b << shift) : (b >> shift);
}

BB Board::rel_shift_down(BB b, uint8_t shift)
{
        return (clr == WHITE) ? (b >> shift) : (b << shift);
}



// HELPERS FOR GENERATING FUNCTIONS OF SLIDING MOVES

void Board::rank_move_gen(BB origin, Piece pce)
{
        uint8_t shift = get_idx(origin) / DIM * DIM;

        BB dest = byte_bb_gen(origin >> shift, all_pieces >> shift);
        general_move_gen(origin, pce, dest << shift);
}

void Board::file_move_gen(BB origin, Piece pce)
{
        BB curr_orig = flipDiag(origin);
        BB curr_occ  = flipDiag(all_pieces);

        uint8_t shift = get_idx(curr_orig) / DIM * DIM;

        BB dest = byte_bb_gen(curr_orig >> shift, curr_occ >> shift);
        dest  <<= shift;

        general_move_gen(origin, pce, flipDiag(dest));
}

void Board::diagonal_move_gen(BB origin, Piece pce)
{
        BB curr_orig = rot_45_c(origin);
        BB curr_occ  = rot_45_c(all_pieces);

        uint8_t shift = get_idx(curr_orig) / DIM * DIM;

        curr_orig >>= shift;
        curr_occ  >>= shift;

        uint8_t left_cnt  = pop_count(byte_bb_gen_left (curr_orig, curr_occ));
        uint8_t right_cnt = pop_count(byte_bb_gen_right(curr_orig, curr_occ));

        BB dest = origin;

        while (left_cnt --)  dest |= dest << 9;
        while (right_cnt --) dest |= dest >> 9;

        dest ^= origin;

        dest &= ~team_pieces[clr];
        general_move_gen(origin, pce, dest);
}

void Board::antidiag_move_gen(BB origin, Piece pce)
{
        BB curr_orig = rot_45_a(origin);
        BB curr_occ  = rot_45_a(all_pieces);

        uint8_t shift = get_idx(curr_orig) / DIM * DIM;

        curr_orig >>= shift;
        curr_occ  >>= shift;

        uint8_t left_cnt  = pop_count(byte_bb_gen_left (curr_orig, curr_occ));
        uint8_t right_cnt = pop_count(byte_bb_gen_right(curr_orig, curr_occ));

        BB dest = origin;

        while (left_cnt --)  dest |= dest >> 7;
        while (right_cnt --) dest |= dest << 7;

        dest ^= origin;

        general_move_gen(origin, pce, dest);
}

uint8_t Board::byte_bb_gen(uint8_t orig, uint8_t occup)
{
        uint8_t left  = byte_bb_gen_left (orig, occup);
        uint8_t right = byte_bb_gen_right(orig, occup);
        return left | right;
}

uint8_t Board::byte_bb_gen_left(uint8_t orig, uint8_t occup)
{
        return (occup - 2 * orig) ^ occup;
}

uint8_t Board::byte_bb_gen_right(uint8_t orig, uint8_t occup)
{
        return rev_bits(byte_bb_gen_left(rev_bits(orig), rev_bits(occup)));
}
