//
// Created by Gabriel Gu on 2018-03-27.
//

#ifndef A5_KING_H
#define A5_KING_H
#include <iostream>
#include <string>
#include "piece.h"

class Board;

class King : public Piece {
    bool first_move;
public:
    King(int x, int y, bool alive, char name, Board *b);
    void produce_next()override;
    bool get_FirstMove();
    void set_FirstMove();
    bool isblock(int r, int c)override;

};


#endif //A5_KING_H



