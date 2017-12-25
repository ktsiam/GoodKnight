#include "basic.h"

static const Bitboard debruijn64 = 0x03f79d71b4cb0a89;
static const uint8_t index64[64] = {
        0,  1, 48,  2, 57, 49, 28,  3, 61, 58, 50, 42, 38, 29, 17,  4,
        62, 55, 59, 36, 53, 51, 43, 22, 45, 39, 33, 30, 24, 18, 12,  5,
        63, 47, 56, 27, 60, 41, 37, 16, 54, 35, 52, 21, 44, 32, 23, 11,
        46, 26, 40, 15, 34, 20, 31, 10, 25, 14, 19,  9, 13,  8,  7,  6
};

//CONVERSION
uint8_t get_idx(BB b)
{
        return index64[((b & -b) * debruijn64) >> 58];
}

BB get_BB(Sq_idx idx)
{
        return 1ull << idx;
}

//ITERATION THROUGH BITS
BB get_lsb(BB b)
{        
        return b & -b;
}

void clear_lsb(BB &b)
{        
        b &= (b-1);
}

BB get_clear_lsb(BB &b)
{
        BB lsb = get_lsb(b);
        b     ^= lsb;
        return lsb;
}
BB get_msb(BB b)
{
        return b ? get_BB(63 - __builtin_clzll(b)) : 0;
}

BB get_clear_msb(BB &b)
{
        BB msb = get_msb(b);
        b     ^= msb;
        return msb;
}

//COMBINATION
BB unite(BB *start, BB *end)
{
        BB u = 0;
        for (BB *bbp = start; bbp != end; ++bbp)
                u |= *bbp;
        return u;
}


//GENERATION
static const BB F_INIT = 0x101010101010101;
static const BB R_INIT = 0xFF;

BB File(uint8_t idx)
{
        assert (idx < DIM && idx >= 0);
        return F_INIT << idx;
}

BB Rank(uint8_t idx)
{
        assert(idx < DIM && idx >= 0);
        return R_INIT << (idx * DIM);
}


//OPERATION
BB shiftBB(BB b, int8_t dx, int8_t dy)
{
        int8_t d = dy * DIM + dx;
        if (d > 0)
                return b << d;
        else
                return b >> (-d);
}

static const uint8_t rev_bit_table[256] { // 256 BYTES
        0, 128, 64, 192, 32, 160, 96, 224, 16, 144, 80, 208, 48, 176, 112, 
        240, 8, 136, 72, 200, 40, 168, 104, 232, 24, 152, 88, 216, 56, 184, 
        120, 248, 4, 132, 68, 196, 36, 164, 100, 228, 20, 148, 84, 212, 52, 
        180, 116, 244, 12, 140, 76, 204, 44, 172, 108, 236, 28, 156, 92, 220, 
        60, 188, 124, 252, 2, 130, 66, 194, 34, 162, 98, 226, 18, 146, 82, 210, 
        50, 178, 114, 242, 10, 138, 74, 202, 42, 170, 106, 234, 26, 154, 90, 218, 
        58, 186, 122, 250, 6, 134, 70, 198, 38, 166, 102, 230, 22, 150, 86, 214, 
        54, 182, 118, 246, 14, 142, 78, 206, 46, 174, 110, 238, 30, 158, 94, 222, 
        62, 190, 126, 254, 1, 129, 65, 193, 33, 161, 97, 225, 17, 145, 81, 209, 49, 
        177, 113, 241, 9, 137, 73, 201, 41, 169, 105, 233, 25, 153, 89, 217, 57, 185, 
        121, 249, 5, 133, 69, 197, 37, 165, 101, 229, 21, 149, 85, 213, 53, 181, 117, 
        245, 13, 141, 77, 205, 45, 173, 109, 237, 29, 157, 93, 221, 61, 189, 125, 253, 
        3, 131, 67, 195, 35, 163, 99, 227, 19, 147, 83, 211, 51, 179, 115, 243, 11, 
        139, 75, 203, 43, 171, 107, 235, 27, 155, 91, 219, 59, 187, 123, 251, 7, 135, 
        71, 199, 39, 167, 103, 231, 23, 151, 87, 215, 55, 183, 119, 247, 15, 143, 79, 
        207, 47, 175, 111, 239, 31, 159, 95, 223, 63, 191, 127, 255
};
uint8_t rev_bits(uint8_t byte)
{
        return rev_bit_table[byte];
}
