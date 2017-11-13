#ifndef TEST_BOARD_H_
#define TEST_BOARD_H_

#include "board.h"

class Test_board : public Board {
public:
        //void front_move(const Move &mv);
        //void back_move (const Move &mv);
        Test_board() = default;
        void print();
        void printBB(BB b);
        void print_moves();
        void custom_move(std::string str);

private:
        std::vector<Move> move_vec;        
};


#endif // TEST_BOARD_H_
