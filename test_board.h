#ifndef TEST_BOARD_H_
#define TEST_BOARD_H_

#include "board.h"

class Test_board : public Board {
public:
        Test_board() = default;
        void print();
        void printBB(BB b);
        void print_moves();
        void custom_move(std::string str);
        void undo();

private:
        void init_move_str();
        std::vector<std::string> move_str;
        std::vector<Move> history;
};


#endif // TEST_BOARD_H_
