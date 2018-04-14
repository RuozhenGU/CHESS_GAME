#ifndef A5_PIECE_H
#define A5_PIECE_H
#include <vector>
#include "cell.h"
#include <iostream>
#include "board.h"
/*#include "king.h"
#include "queen.h"
#include "rook.h"
#include "bishop.h"
#include "knight.h"
#include "pawn.h"
*/
class Piece {
protected:
    int x;
    int y;
    int x_prev;
    int y_prev;
    bool alive;
    char chess_name;
    std::vector<std::vector<int>> next_move;
    Board *b;
    int power;
public:
    Piece(int x, int y, bool alive, char chess_name, Board* b) :
            x{ x }, y{ y }, x_prev{ x }, y_prev{ y }, alive{ alive },
            chess_name{ chess_name }, b{ b }{}
    void SetX(int x) { this->x = x; }
    void SetY(int y) { this->y = y; }
    void SetX_prev(int x) { this->x_prev = x; }
    void SetY_prev(int y) { this->y_prev = y; }
    void SetAlive() { this->alive = !alive; }
    int getX() { return x; }
    int getY() { return y; }
    int getX_prev() { return x_prev; }
    int getY_prev() { return y_prev; }
    std::vector<std::vector<int>> & getNext_move() { return this->next_move; }
    bool getAlive() { return alive; }
    virtual void produce_next() = 0;
    virtual bool attack(int x, int y);
    bool is_alive();
    char get_name();
    virtual bool isblock(int r, int c) = 0; //check if there is any cell between c and current piece
    int get_power() { return power; }
    void set_power(int a) { power = a; }
};
// note getNext_move is returning a reference to vector
// note when constrrruct a piece, give its x and y, alive. for x_prev, set it as -1
#endif //A5_PIECE_H


