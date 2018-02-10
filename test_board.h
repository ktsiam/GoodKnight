#ifndef TEST_BOARD_H_
#define TEST_BOARD_H_

#include "move_maker.h"
#include "move_generator.h"

class Test_board : public Move_maker, public Move_generator {
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
