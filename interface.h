#ifndef INTERFACE_H_
#define INTERFACE_H_

#include "traverser.h"

class Interface : private Traverser {
public:
        Interface();
        ~Interface() = default;

        void interactive();
        void one_player();
        void two_player();
        
private:

        void analysis();
        bool player_move(std::string mv); //ret if valid
        void computer_move();
        void undo();
        void init_move_str();
        void render_analysis();
        void render_moves();
        void render_board();
        
        std::vector<std::string> move_str;
};


#endif // INTERFACE_H_
