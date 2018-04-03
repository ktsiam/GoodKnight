#include "interface.h"
#include <string>
#include <iostream>

void usage();
int main(int argc, char *argv[]) 
{
        Interface inter;
        if (argc == 1)
                usage();
        else if (std::string(argv[1]) == "-i")
                inter.interactive();
        else if (std::string(argv[1]) == "-two")
                inter.two_player();
        else if (std::string(argv[1]) == "-one")
                inter.one_player();
        else usage();
        
        return 0;
}

void usage()
{
        std::cout << "Flags: "
                  << "\n\t `-one` --> One-player chess [default]"
                  << "\n\t `-two` --> Two-player chess"
                  << "\n\t `-i`   --> Interactive mode"
                  << "\n\nInteractive Keys: "
                  << "\n\t`[SQ][SQ]` --> Move  (e.g. `e2e4`)"
                  << "\n\t`cpu`      --> Let engine move"
                  << "\n\t`analysis  --> Analyze position"
                  << "\n\t`undo`     --> Takes back last move"
                  << "\n\t`quit`     --> Quits engine"
                  << "\n\n\t[Initials for these instructions are recognized]\n";
        exit(1);
}
