#ifndef BASIC_H_
#define BASIC_H_

#include <cstdint>
#include <cassert>
#include <string>

typedef uint64_t Bitboard;
typedef Bitboard BB;
typedef uint8_t Sq_idx;

enum Color    : uint8_t { WHITE, BLACK, CLR_NB };
enum Piece    : uint8_t { K, Q, R, B, N, P, PIECE_NB = 6 };
enum Castling : uint8_t { NO_CASTLING, O_O, O_O_O };

const uint8_t DIM = 8;

uint8_t get_idx   (BB b);
BB      clear_lsb (BB b);
BB      get_lsb   (BB b);
BB      get_BB    (Sq_idx idx);
BB      unite     (BB *start, BB *end);
BB      SQ        (std::string s);

#endif // BASIC_H_
