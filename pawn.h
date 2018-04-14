#ifndef PAWN_H
#define PAWN_H

#include "piece.h"
#include <iostream>
#include <string>
class Board;

class Pawn : public Piece {
    int promoted;//true means this piece is promoted, no point of using this piece
    int first_move; //used to see if adding (x y+2) into the next move vector
public:
    Pawn(int x, int y, bool alive, char name, Board *b);
    void produce_next()override;
    bool get_promoted();
    void set_promoted();
    bool get_FirstMove();
    void set_FirstMove();
    bool isblock(int r, int c)override;
    bool attack(int x, int y)override;
};


#endif //A5_PAWN_H



