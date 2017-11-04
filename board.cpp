#include "board.h"

Board::Board(BB ks[], BB qs[], BB rs[], BB bs[], BB ns[], BB ps[], Color c)
{
        for (int i = 0; i < 2; ++i) {
                k[i] = ks[i];
                q[i] = qs[i];
                r[i] = rs[i];
                b[i] = bs[i];
                n[i] = ns[i];
                p[i] = ps[i];
        }
        clr  = c;
        en_passant = 0;
}

Board::Board()
{
        k[0] = SQ("E1"),          k[1] = SQ("E8");
        q[0] = SQ("D1"),          q[1] = SQ("D8");
        r[0] = SQ("A1")|SQ("A8"), r[1] = SQ("H1")|SQ("H8");
        b[0] = SQ("C1")|SQ("F1"), b[1] = SQ("C8")|SQ("F8");
        n[0] = SQ("B1")|SQ("G1"), n[1] = SQ("B8")|SQ("G8");
        p[0] = Rank(1),           p[1] = Rank(6);
        clr = WHITE;
        en_passant = 0;
}
