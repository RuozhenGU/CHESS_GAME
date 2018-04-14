#include "pawn.h"
#include "cell.h"
#include <vector>
#include <iostream>
#include <string>
using namespace std;

Pawn::Pawn(int x, int y, bool alive, char name, Board *b) :
Piece{ x, y, alive, name, b } ,promoted{ false } {
    this->produce_next();
}

void Pawn::produce_next() {
    next_move.clear();
    
    if (x_prev == x && y_prev == y) { //first move
        if(chess_name == 'P' && y + 2 <= 7) {  //white pieces
            vector<int> Cell1{ x, y + 2 };
            if (y+2 <=7) next_move.emplace_back(Cell1);
        }
        else if(chess_name == 'p' && y - 2 >= 0) { //black pieces
            vector<int> Cell1{ x, y - 2 };
            if (y-2>=0) next_move.emplace_back(Cell1);
        }
    }
    
    //first move or not
    if(chess_name == 'P' && y + 1 <= 7) {  //white pieces
        vector<int> Cell2{ x, y + 1 };
        vector<int> Cell3{ x + 1, y + 1 };
        vector<int> Cell4{ x - 1, y + 1 };
        if (y+1<=7&&x+1<=7)next_move.emplace_back(Cell3);
        if (x-1>=0&&y+1<=7)next_move.emplace_back(Cell4);
        if (y+1<=7)next_move.emplace_back(Cell2);
    }
    else if(chess_name == 'p' && y - 1 >= 0) { //black pieces
        vector<int> Cell2{ x, y - 1 };
        vector<int> Cell3{ x + 1, y - 1 };
        vector<int> Cell4{ x - 1, y - 1 };
        if (y-1>=0&&x+1<=7)next_move.emplace_back(Cell3);
        if (y-1>=0&&x-1>=0)next_move.emplace_back(Cell4);
        if (y-1>=0)next_move.emplace_back(Cell2);
    }
}

bool Pawn::get_promoted() { return promoted; }

void Pawn::set_promoted() { promoted = !promoted; }

bool Pawn::get_FirstMove() { return first_move; }

void Pawn::set_FirstMove() { first_move = !first_move; }

bool Pawn::isblock(int r, int c) {
    if(r == x) {
        for (auto i = next_move.begin(); i != next_move.end(); i++) {
            if ((*i)[0] == x && b->check_occupied((*i)[0], (*i)[1])) return true;
        }
    }
    return false;
}
bool Pawn::attack(int x, int y) {
    for (auto it = next_move.begin(); it != next_move.end(); it++) {
        if ((*it)[0] == x && (*it)[1] == y && isblock(x,y) == false) {
            return true;
        }
    }
    return false;
}


