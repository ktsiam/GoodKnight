#ifndef BASIC_H_
#define BASIC_H_

#include <cstdint>
#include <cassert>
#include <string>

typedef uint64_t Bitboard;
typedef Bitboard BB;
typedef uint8_t Sq_idx;

enum Color    : uint8_t { WHITE, BLACK, CLR_NB };
enum Piece    : uint8_t { NO_PIECE, KING, QUEEN, ROOK, BISHOP, KNIGHT,
                          PAWN, PIECE_NB = 7};

enum Castling : uint8_t { NO_CASTLING, O_O, O_O_O, BOTH };
enum Direction:  int8_t { NORTH = 8, SOUTH = -8, EAST = 1,  WEST = -1, 
                          NW    = 7, NE = 9    , SW   = -9, SE   = -7 }

const uint8_t DIM = 8;

uint8_t get_idx   (BB b);               // returns index of lsb
BB      clear_lsb (BB b);               // clears lsb
BB      get_lsb   (BB b);               // returns BB with lsb
BB      get_BB    (Sq_idx idx);         // returns BB with set given bit
BB      unite     (BB *start, BB *end); // merges all BBs from start to end
                                       
BB      File      (uint8_t idx);        // returns file BB of given index
BB      Rank      (uint8_t idx);        // returns rank BB of given index
BB      SQ        (std::string s);      // returns BB with given square

#endif // BASIC_H_
