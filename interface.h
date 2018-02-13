#ifndef INTERFACE_H_
#define INTERFACE_H_

#include "traverser.h"

class Interface : public Traverser {
public:
        Interface();
        ~Interface() = default;
        
        void custom_move(std::string str);

private:

        void undo();
        void print();
        void print_moves();
        void init_move_str();
        
        std::vector<std::string> move_str;
};


#endif // INTERFACE_H_
