//
// Created by Gabriel Gu on 2018-03-27.
//

#ifndef A5_ROOK_H
#define A5_ROOK_H

#include "piece.h"
#include <iostream>
#include <string>
class Board;


class Rook : public Piece {
    bool first_move;
public:
    Rook(int x, int y, bool alive, char name, Board *b);
    void produce_next()override;
    bool get_FirstMove();
    void set_FirstMove();
    bool isblock(int r, int c)override;
    bool attack(int x, int y)override;
};


#endif //A5_ROOK_H



