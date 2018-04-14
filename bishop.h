//
// Created by Gabriel Gu on 2018-03-27.
//

#ifndef A5_BISHOP_H
#define A5_BISHOP_H

#include "piece.h"
#include <iostream>
#include <string>
class Board;

class Bishop : public Piece {

public:
    Bishop(int x, int y, bool alive, char name, Board *b);
    void produce_next()override;
    bool isblock(int r, int c)override;
    bool attack(int x, int y)override;

};


#endif //A5_BISHOP_H



