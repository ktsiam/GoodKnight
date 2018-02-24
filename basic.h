// Can improve file and rank function (given through multiplication and shift)

#ifndef BASIC_H_
#define BASIC_H_

#include <cstdint>
#include <cassert>
#include <string>

//Branch prediction helpers
#define LIKELY(condition)   __builtin_expect(static_cast<bool>(condition), 1)
#define UNLIKELY(condition) __builtin_expect(static_cast<bool>(condition), 0)

#define SQ(s) (File(s[0] - 'A') & Rank(s[1] - '1'))

typedef uint8_t  Sq_idx;
typedef int32_t  Score;
typedef uint64_t BB;

enum Color    : uint8_t { WHITE, BLACK, CLR_NB };
enum Castling : uint8_t { NO_CASTLING, O_O, O_O_O, BOTH };
enum Piece    : uint8_t { KING, QUEEN, ROOK, BISHOP, KNIGHT,
                          PAWN, PIECE_NB = 6, NO_PIECE = 7 };
const uint8_t DIM = 8;

//debugging
void print(BB b);

//conversion
uint8_t get_idx   (BB b);               // returns index of lsb
BB      get_BB    (Sq_idx idx);         // returns BB with set given bit

//iterate through bits
BB      get_lsb   (BB b);               // returns BB with lsb
void    clear_lsb (BB &b);              // clears lsb
BB      get_clear_lsb(BB &b);           // returns BB with lsb and clears
BB      get_msb   (BB b);               // returns BB with msb
BB      get_clear_msb(BB &b);           // returns BB with msb and clears
BB      pop_count (BB b);               // returns number of set bits

//combine BBs
BB      unite     (BB *start, BB *end); // merges all BBs from start to end

//generate BBs
BB      File      (uint8_t idx);        // returns file BB of given index
BB      Rank      (uint8_t idx);        // returns rank BB of given index

//operation
BB      flipDiag   (BB b);             // flips a1-h8
BB      rot_45_c   (BB b);             // maps diagonals to files
BB      rot_45_a   (BB b);             // maps anti-diagonals to files
uint8_t rev_bits   (uint8_t byte);     // returns BYTE with reversed bits

#endif // BASIC_H_
