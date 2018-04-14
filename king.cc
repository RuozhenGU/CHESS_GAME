#include "king.h"
#include "cell.h"
#include "board.h"
#include <vector>
#include <iostream>
#include <string>
using namespace std;

King::King(int x, int y, bool alive, char name, Board *b) :
Piece{ x, y, alive, name,b }, first_move{ false }{
	this->produce_next();
}

void King::produce_next() {
	for (auto item = next_move.begin(); item != next_move.end(); item++) {
		(*item).clear();
	}
	next_move.clear();
	/*if (first_move == false) {
		if (x_prev != x || y_prev != y) first_move = true;
	} */
	if(x-1 >=0 && y -1 >= 0) {
		vector<int> Cell1{ x - 1, y - 1 };
		next_move.emplace_back(Cell1);
	}
	if(x-1 >=0) {
		vector<int> Cell2{ x - 1, y };
		next_move.emplace_back(Cell2);
	}
	if(x-1 >=0 && y+1 <= 7) {
		vector<int> Cell3{ x - 1, y + 1 };
		next_move.emplace_back(Cell3);
	}
	if(y-1 >= 0) {
		vector<int> Cell4{ x, y - 1 };
		next_move.emplace_back(Cell4);
	}
	if(y+1 <= 7) {
		vector<int> Cell5{ x, y + 1 };
		next_move.emplace_back(Cell5);
	}
	if(x+1 <=7 && y-1 >= 0) {
		vector<int> Cell6{ x + 1, y - 1 };
		next_move.emplace_back(Cell6);
	}
	if(x+1 <=7 ) {
		vector<int> Cell7{ x + 1, y };
		next_move.emplace_back(Cell7);
	}
	if(x+1 <=7 && y+1 <= 7) {
		vector<int> Cell8{ x + 1, y + 1 };
		next_move.emplace_back(Cell8);
	}	
	
}

bool King::get_FirstMove() { return first_move; }

void King::set_FirstMove() { first_move = !first_move; }

bool King::isblock(int r, int c) {
	
	return false;
}





