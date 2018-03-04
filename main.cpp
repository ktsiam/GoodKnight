#include <iostream>

#include "interface.h"

enum COMMANDS { CPU_MOVE, PLAYER_MOVE, ANALYSIS, UNDO, QUIT };

COMMANDS decode(std::string s);
void clear() { std::cout << "\n\n\n\n\n\n\n\n\n"; }

int main() 
{        
        Interface chess;

        std::string s;
        while (std::cin >> s) {
                switch (decode(s)) {                        
                case QUIT        : return 0;
                        
                case UNDO        : clear();
                        chess.undo();          break;
                        
                case ANALYSIS    : clear();
                        chess.analysis();      break;
                        
                case CPU_MOVE    : clear();
                        chess.computer_move(); break;
                        
                case PLAYER_MOVE : clear();
                        chess.player_move(s);  break;
                }
        }
        return 0;
}

COMMANDS decode(std::string s)
{
        if (s == "q" || s == "Q"
            || s == "quit"
            || s == "exit")          return QUIT;
        if (s == "u" || s == "U"
            || s == "undo"
            || s == "r" || s == "R") return UNDO;
        if (s == "a" || s == "e"
            || s == "analysis"
            || s == "analyze"
            || s == "eval"
            || s == "evaluate"
            || s == "score")      return ANALYSIS;       
        if (s == "c" || s == "cpu"
            || s == "computer"
            || s == "move"
            || s == "play"
            || s == "engine")     return CPU_MOVE;
        
        return PLAYER_MOVE;
}
