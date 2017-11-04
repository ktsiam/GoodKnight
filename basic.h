#ifndef BASIC_H_
#define BASIC_H_

#include <cstdint>
#include <cassert>

typedef uint64_t Bitboard;
typedef Bitboard BB;
typedef uint8_t Sq_idx;

enum Color: uint8_t { WHITE, BLACK, CLR_NB };
enum Piece : uint8_t { K, Q, R, B, N, P, PIECE_NB = 6 };
enum Castling : uint8_t { NO_CASTLING, O_O, O_O_O };
const uint8_t DIM = 8;

inline uint8_t get_idx(BB b);
inline BB clear_lsb   (BB b);
inline BB get_lsb     (BB b);
inline BB unite       (BB *start, BB *end);

enum Square : BB{
                A1 = 1ull<<0,  B1 = 1ull<<1,  C1 = 1ull<<2,  D1 = 1ull<<3,
                E1 = 1ull<<4,  F1 = 1ull<<5,  G1 = 1ull<<6,  H1 = 1ull<<7,
                A2 = 1ull<<8,  B2 = 1ull<<9,  C2 = 1ull<<10, D2 = 1ull<<11,
                E2 = 1ull<<12, F2 = 1ull<<13, G2 = 1ull<<14, H2 = 1ull<<15,
                A3 = 1ull<<16, B3 = 1ull<<17, C3 = 1ull<<18, D3 = 1ull<<19,
                E3 = 1ull<<20, F3 = 1ull<<21, G3 = 1ull<<22, H3 = 1ull<<23,
                A4 = 1ull<<24, B4 = 1ull<<25, C4 = 1ull<<26, D4 = 1ull<<27,
                E4 = 1ull<<28, F4 = 1ull<<29, G4 = 1ull<<30, H4 = 1ull<<31,
                A5 = 1ull<<32, B5 = 1ull<<33, C5 = 1ull<<34, D5 = 1ull<<35,
                E5 = 1ull<<36, F5 = 1ull<<37, G5 = 1ull<<38, H5 = 1ull<<39,
                A6 = 1ull<<40, B6 = 1ull<<41, C6 = 1ull<<42, D6 = 1ull<<43,
                E6 = 1ull<<44, F6 = 1ull<<45, G6 = 1ull<<46, H6 = 1ull<<47,
                A7 = 1ull<<48, B7 = 1ull<<49, C7 = 1ull<<50, D7 = 1ull<<51,
                E7 = 1ull<<52, F7 = 1ull<<53, G7 = 1ull<<54, H7 = 1ull<<55,
                A8 = 1ull<<56, B8 = 1ull<<57, C8 = 1ull<<58, D8 = 1ull<<59,
                E8 = 1ull<<60, F8 = 1ull<<61, G8 = 1ull<<62, H8 = 1ull<<63,
};

#endif // BASIC_H_
