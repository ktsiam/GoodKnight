// Can improve file and rank function (given through multiplication and shift)

#ifndef BASIC_H_
#define BASIC_H_

#include <cstdint>
#include <cassert>
#include <string>

typedef uint64_t Bitboard;
typedef Bitboard BB;
typedef uint8_t Sq_idx;

enum Color    : uint8_t { WHITE, BLACK, CLR_NB };
enum Castling : uint8_t { NO_CASTLING, O_O, O_O_O, BOTH };
enum Piece    : uint8_t { KING, QUEEN, ROOK, BISHOP, KNIGHT,
                          PAWN, PIECE_NB = 6, NO_PIECE = 7 };

const uint8_t DIM = 8;

//conversion
uint8_t get_idx   (BB b);               // returns index of lsb
BB      get_BB    (Sq_idx idx);         // returns BB with set given bit

//iterate through bits
BB      get_lsb   (BB b);               // returns BB with lsb
void    clear_lsb (BB &b);              // clears lsb
BB      get_clear_lsb(BB &b);           // returns BB with lsb and clears
BB      get_msb   (BB b);               // returns BB with msb
BB      get_clear_msb(BB &b);           // returns BB with msb and clears

//combine BBs
BB      unite     (BB *start, BB *end); // merges all BBs from start to end

//generate BBs
BB      File      (uint8_t idx);        // returns file BB of given index
BB      Rank      (uint8_t idx);        // returns rank BB of given index

//operation
BB      shiftBB   (BB b, int8_t dx, int8_t dy); //shifts BB as shown

//extra
uint8_t rev_bits  (uint8_t byte);       // returns BYTE with reversed bits

#endif // BASIC_H_
