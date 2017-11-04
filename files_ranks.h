#ifndef FILES_RANKS_H_
#define FILES_RANKS_H_

#include "basic.h"

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
        return R_INIT << (idx * 8);
}

#endif // FILES_RANKS_H_
