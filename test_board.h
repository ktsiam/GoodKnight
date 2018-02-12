#ifndef TEST_BOARD_H_
#define TEST_BOARD_H_

#include "traverser.h"

class Test_board : public Traverser {
public:
        Test_board();
        ~Test_board() = default;
        
        void print();
        void print_moves();
        void custom_move(std::string str);
        void undo();

private:
        void init_move_str();
        std::vector<std::string> move_str;
};


#endif // TEST_BOARD_H_
