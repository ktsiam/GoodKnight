#ifndef MOVE_MAKER_
#define MOVE_MAKER_

#include "board.h"

class Move_maker : virtual public Board {
public:
        Move_maker()  = default;
        ~Move_maker() = default;

        bool front_move(const Move mv) override;
        void back_move ()              override;

private:
        //front_move - back_move helpers
        void castle(Castling cstl, Color c);
        void en_passant(BB org, BB dest, Color c);
        bool capture(BB dest, Piece pce, Color c);
        void promote(BB org, BB dest, Piece new_pce, Color c);
        void displace(BB org, BB dest, Piece pce, Color c);
        void set_en_passant(BB org, BB dest);
        
};
#endif // MOVE_MAKER_
