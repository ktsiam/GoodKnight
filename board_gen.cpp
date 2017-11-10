#include "board.h"

static const BB KNIGHT_MOVE[DIM*DIM] = {
        0x20400, 0x50800, 0xa1100, 0x142200,
        0x284400, 0x508800, 0xa01000, 0x402000,
        0x2040004, 0x5080008, 0xa110011, 0x14220022,
        0x28440044, 0x50880088, 0xa0100010, 0x40200020,
        0x204000402, 0x508000805, 0xa1100110a, 0x1422002214,
        0x2844004428, 0x5088008850, 0xa0100010a0, 0x4020002040,
        0x20400040200, 0x50800080500, 0xa1100110a00, 0x142200221400,
        0x284400442800, 0x508800885000, 0xa0100010a000, 0x402000204000,
        0x2040004020000, 0x5080008050000, 0xa1100110a0000, 0x14220022140000,
        0x28440044280000, 0x50880088500000, 0xa0100010a00000, 0x40200020400000,
        0x204000402000000, 0x508000805000000, 0xa1100110a000000, 0x1422002214000000,
        0x2844004428000000, 0x5088008850000000, 0xa0100010a0000000, 0x4020002040000000,
        0x400040200000000,  0x800080500000000,  0x1100110a00000000, 0x2200221400000000,
        0x4400442800000000, 0x8800885000000000, 0x100010a000000000, 0x2000204000000000,
        0x4020000000000,    0x8050000000000,    0x110a0000000000,   0x22140000000000,
        0x44280000000000,   0x88500000000000,   0x10a00000000000,  0x20400000000000
};

static const BB KING_MOVE[DIM*DIM] = {
        0x302, 0x705, 0xe0a, 0x1c14,
        0x3828, 0x7050, 0xe0a0, 0xc040,
        0x30203, 0x70507, 0xe0a0e, 0x1c141c,
        0x382838, 0x705070, 0xe0a0e0, 0xc040c0,
        0x3020300, 0x7050700, 0xe0a0e00, 0x1c141c00,
        0x38283800, 0x70507000, 0xe0a0e000, 0xc040c000,
        0x302030000, 0x705070000, 0xe0a0e0000, 0x1c141c0000,
        0x3828380000, 0x7050700000, 0xe0a0e00000, 0xc040c00000,
        0x30203000000, 0x70507000000, 0xe0a0e000000, 0x1c141c000000,
        0x382838000000, 0x705070000000, 0xe0a0e0000000, 0xc040c0000000,
        0x3020300000000, 0x7050700000000, 0xe0a0e00000000, 0x1c141c00000000,
        0x38283800000000, 0x70507000000000, 0xe0a0e000000000, 0xc040c000000000,
        0x302030000000000, 0x705070000000000, 0xe0a0e0000000000, 0x1c141c0000000000,
        0x3828380000000000, 0x7050700000000000, 0xe0a0e00000000000, 0xc040c00000000000,
        0x203000000000000,  0x507000000000000,  0xa0e000000000000,  0x141c000000000000,
        0x2838000000000000, 0x5070000000000000, 0xa0e0000000000000, 0x40c0000000000000
};

static const BB PAWN_ATTACK[DIM*DIM] = {
        0x0, 0x0, 0x0, 0x0, 
        0x0, 0x0, 0x0, 0x0, 
        0x20000, 0x50000, 0xa0000, 0x140000, 
        0x280000, 0x500000, 0xa00000, 0x400000, 
        0x2000000, 0x5000000, 0xa000000, 0x14000000, 
        0x28000000, 0x50000000, 0xa0000000, 0x40000000, 
        0x200000000, 0x500000000, 0xa00000000, 0x1400000000, 
        0x2800000000, 0x5000000000, 0xa000000000, 0x4000000000, 
        0x20000000000, 0x50000000000, 0xa0000000000, 0x140000000000, 
        0x280000000000, 0x500000000000, 0xa00000000000, 0x400000000000, 
        0x2000000000000, 0x5000000000000, 0xa000000000000, 0x14000000000000, 
        0x28000000000000, 0x50000000000000, 0xa0000000000000, 0x40000000000000, 
        0x200000000000000, 0x500000000000000, 0xa00000000000000, 0x1400000000000000, 
        0x2800000000000000, 0x5000000000000000, 0xa000000000000000, 0x4000000000000000
};

void Board::init_variables()
{
        all_pieces[WHITE] = unite(&pieces[WHITE][KING], &pieces[WHITE][PIECE_NB]);
        all_pieces[BLACK] = unite(&pieces[BLACK][KING], &pieces[BLACK][PIECE_NB]);
}

BB Board::knight_move_gen()
{        
        BB knight_moves = 0;
        BB knight = pieces[clr][KNIGHT];
        while (knight != 0) {

                uint8_t lsb = get_idx(get_lsb(knight));
                knight_moves |= KNIGHT_MOVE[lsb];
                knight = clear_lsb(knight);
        }
        return knight_moves & ~all_pieces[clr];
}

BB Board::king_move_gen()
{        
        BB king_moves = 0;
        BB king = pieces[clr][KING];
        while (king != 0) {

                uint8_t lsb = get_idx(get_lsb(king));
                king_moves |= KING_MOVE[lsb];
                king = clear_lsb(king);
        }
        return king_moves & ~all_pieces[clr];
}


BB Board::pawn_move_gen()
{
        BB pawn_moves = 0;
        BB pawn_attacks = 0;
        BB pawn = pieces[clr][PAWN];
        while (pawn != 0) {
                uint8_t lsb = get_idx(get_lsb(pawn));
                pawn_attacks |= PAWN_ATTACK[lsb];
                pawn_moves   |= shiftBB(get_lsb(pawn), 0, (clr==WHITE) ? 1 : -1);
                pawn = clear_lsb(pawn);
        }
        
        pawn_attacks &= all_pieces[clr^1] | en_passant_sq;
        pawn_moves   &= ~(all_pieces[clr] & all_pieces[clr^1]);        

        return pawn_moves;
}
