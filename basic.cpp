#include "basic.h"

BB clear_lsb(BB b)
{
        assert(b);
        return b & (b-1);
}

BB get_lsb(BB b)
{
        assert(b);
        return b & -b;
}

BB unite(BB *start, BB *end)
{
        BB u = 0;
        for (BB *bbp = start; bbp != end; ++bbp)
                u |= *bbp;
        return u;
}

static const Bitboard debruijn64 = 0x03f79d71b4cb0a89;
static const uint8_t index64[64] = {
        0,  1, 48,  2, 57, 49, 28,  3, 61, 58, 50, 42, 38, 29, 17,  4,
        62, 55, 59, 36, 53, 51, 43, 22, 45, 39, 33, 30, 24, 18, 12,  5,
        63, 47, 56, 27, 60, 41, 37, 16, 54, 35, 52, 21, 44, 32, 23, 11,
        46, 26, 40, 15, 34, 20, 31, 10, 25, 14, 19,  9, 13,  8,  7,  6
};

uint8_t get_idx(BB b)
{
        assert (b != 0);
        return index64[((b & -b) * debruijn64) >> 58];
}

BB SQ(std::string s)
{
        BB file = s[0]-'A';
        BB rank = s[1]-'1';
        return 1ull << (8 * rank + file);
}
