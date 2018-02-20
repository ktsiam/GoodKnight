#include "basic.h"


static const BB debruijn64 = 0x03f79d71b4cb0a89;
static const uint8_t index64[DIM*DIM] = {
        0,  1, 48,  2, 57, 49, 28,  3, 61, 58, 50, 42, 38, 29, 17,  4,
        62, 55, 59, 36, 53, 51, 43, 22, 45, 39, 33, 30, 24, 18, 12,  5,
        63, 47, 56, 27, 60, 41, 37, 16, 54, 35, 52, 21, 44, 32, 23, 11,
        46, 26, 40, 15, 34, 20, 31, 10, 25, 14, 19,  9, 13,  8,  7,  6
};

//CONVERSION
uint8_t get_idx(BB b)
{
        return index64[(b * debruijn64) >> 58];
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

BB pop_count(const BB b)
{
        return  __builtin_popcountll(b);
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

static const uint8_t rev_bit_table[16] = {
        0x0, 0x8, 0x4, 0xC, 0x2, 0xA, 0x6, 0xE,
        0x1, 0x9, 0x5, 0xD, 0x3, 0xB, 0x7, 0xF
};

uint8_t rev_bits(uint8_t byte)
{
        return (rev_bit_table[byte & 0xF] << 4) |
                rev_bit_table[byte >> 4];
}

BB flipDiag(BB x) 
{
        BB t;
        static const BB k1 = 0x5500550055005500;
        static const BB k2 = 0x3333000033330000;
        static const BB k4 = 0x0f0f0f0f00000000;
        t  = k4 & (x ^ (x << 28));
        x ^=       t ^ (t >> 28) ;
        t  = k2 & (x ^ (x << 14));
        x ^=       t ^ (t >> 14) ;
        t  = k1 & (x ^ (x <<  7));
        x ^=       t ^ (t >>  7) ;
        return x;
}

static BB rotateRight(BB x, int s)
{
        return (x >> s) | (x << (64-s));
}

BB rot_45_c(BB x)
{
        const BB k1 = 0xAAAAAAAAAAAAAAAA;
        const BB k2 = 0xCCCCCCCCCCCCCCCC;
        const BB k4 = 0xF0F0F0F0F0F0F0F0;
        x ^= k1 & (x ^ rotateRight(x,  8));
        x ^= k2 & (x ^ rotateRight(x, 16));
        x ^= k4 & (x ^ rotateRight(x, 32));
        return x;
}

BB rot_45_a(BB x)
{
        const BB k1 = 0x5555555555555555;
        const BB k2 = 0x3333333333333333;
        const BB k4 = 0x0f0f0f0f0f0f0f0f;
        x ^= k1 & (x ^ rotateRight(x,  8));
        x ^= k2 & (x ^ rotateRight(x, 16));
        x ^= k4 & (x ^ rotateRight(x, 32));
        return x;
}



//debugging
#include <iostream>
void print(BB b)
{
        for (int r = 7; r >= 0; --r){
                std::cout << r+1 << " ";
                for (int f = 0; f < 8; ++f)
                        std::cout << "_o"[(bool)(b & 1ULL << (8*r+f))] << " ";
                std::cout << "\n";
        }
        std::cout << "  A B C D E F G H\n\n";
}

