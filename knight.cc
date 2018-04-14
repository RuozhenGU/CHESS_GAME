//
// Created by Gabriel Gu on 2018-03-27.
//

#include "knight.h"
#include "cell.h"
#include <vector>
#include <iostream>
#include <string>
using namespace std;

Knight::Knight(int x, int y, bool alive, char name, Board *b) :
Piece{ x, y, alive, name, b }{
    this->produce_next();
}

void Knight::produce_next() {
    for (auto item = next_move.begin(); item != next_move.end(); item++) {
        (*item).clear();
    }
    next_move.clear();
    
    vector<int> Cell1{ x + 2, y - 1 };
    vector<int> Cell2{ x + 2, y + 1 };
    vector<int> Cell3{ x - 2, y - 1 };
    vector<int> Cell4{ x - 2, y + 1 };
    vector<int> Cell5{ x + 1, y + 2 };
    vector<int> Cell6{ x + 1, y - 2 };
    vector<int> Cell7{ x - 1, y + 2 };
    vector<int> Cell8{ x - 1, y - 2 };
    
    if(x + 2 <= 7 && y - 1 >= 0) next_move.emplace_back(Cell1);
    if(x + 2 <= 7 && y + 1 <= 7) next_move.emplace_back(Cell2);
    if(x - 2 >= 0 && y - 1 >= 0) next_move.emplace_back(Cell3);
    if(x - 2 >= 0 && y + 1 <= 7) next_move.emplace_back(Cell4);
    if(x + 1 <= 7 && y + 2 <= 7) next_move.emplace_back(Cell5);
    if(x + 1 <= 7 && y - 2 >= 0) next_move.emplace_back(Cell6);
    if(x - 1 >= 0 && y + 2 <= 7) next_move.emplace_back(Cell7);
    if(x - 1 >= 0 && y - 2 >= 0) next_move.emplace_back(Cell8);
}

bool Knight::isblock(int r, int c) { return false; }

bool Knight::attack(int x, int y) {
    for (auto it = next_move.begin(); it != next_move.end(); it++) {
        if ((*it)[0] == x && (*it)[1] == y && isblock(x,y) == false) {
            return true;
        }
    }
    return false;
}


