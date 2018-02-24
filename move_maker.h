#ifndef MOVE_MAKER_
#define MOVE_MAKER_

#include "board.h"

class Move_maker : virtual public Board {
public:
        Move_maker()  = default;
        ~Move_maker() = default;

        void front_move(const Move mv) override;
        void back_move ()              override;

private:
        //front_move - back_move helpers
        void castle(Castling cstlc);
        void en_passant(BB org, BB dest);
        void capture(BB dest, Piece pce);
        void promote(BB org, BB dest, Piece new_pce);
        void displace(BB org, BB dest, Piece pce);
        void set_en_passant(BB org, BB dest);
        void check_castling(Color c);
        
};
#endif // MOVE_MAKER_
