//
// Created by Gabriel Gu on 2018-03-27.
//

#ifndef A5_KNIGHT_H
#define A5_KNIGHT_H

#include "piece.h"
#include <iostream>
#include <string>

class Board;

class Knight : public Piece {

public:
    Knight(int x, int y, bool alive, char name, Board *b);
    void produce_next()override;
    bool isblock(int r, int c)override;
    bool attack(int x, int y)override;
};

#endif //A5_KNIGHT_H



