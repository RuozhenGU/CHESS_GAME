#include "board.h"
#include "cell.h"
#include "textdisplay.h"
#include "graphicaldisplay.h"
#include "window.h"
#include <string>


using namespace std;
class Cell;

Board::Board(){
	theBoard.clear();

	//create a textdisplay
	td = make_shared<TextDisplay>();
	gd = make_shared<GraphicalDisplay>();
	for (int i = 0; i < 8; ++i){
		theBoard.emplace_back();
		for (int j = 0; j < 8; ++j){
			theBoard[i].emplace_back(Cell{ 'Z', i, j });
		}
	}

}


Cell* Board::get_cell(int x, int y){
	return &theBoard[x][y];
}

void Board::init(){
	
	for (int i = 0; i < 8; ++i){
		theBoard.emplace_back();
		for (int j = 0; j < 8; ++j){
			theBoard[i][j].set_occupied('Z');
		}
	}

	theBoard[0][0].set_occupied('R'); 
	theBoard[1][0].set_occupied('N');
	theBoard[2][0].set_occupied('B');
	theBoard[3][0].set_occupied('Q');
	theBoard[4][0].set_occupied('K');
	theBoard[5][0].set_occupied('B');
	theBoard[6][0].set_occupied('N');
	theBoard[7][0].set_occupied('R');

	
	for (int j = 0; j < 8; ++j){
		theBoard[j][1].set_occupied('P');
	}


	for (int j = 0; j < 8; ++j){
		theBoard[j][6].set_occupied('p');
	}

	theBoard[0][7].set_occupied('r');
	theBoard[1][7].set_occupied('n');
	theBoard[2][7].set_occupied('b');
	theBoard[3][7].set_occupied('q');
	theBoard[4][7].set_occupied('k');
	theBoard[5][7].set_occupied('b');
	theBoard[6][7].set_occupied('n');
	theBoard[7][7].set_occupied('r');


	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j){
			theBoard[i][j].notifyDisplay(td,gd);

		}
	}
}

void Board::initsetup(){
    for (int i = 0; i < 8; ++i){
        theBoard.emplace_back();
        for (int j = 0; j < 8; ++j){
            theBoard[i][j].set_occupied('Z');
            theBoard[i][j].notifyDisplay(td,gd);
        }
    }
    
}


void Board::place(char name, int x, int y){
	theBoard[x][y].setX(x);
	theBoard[x][y].setY(y);
	theBoard[x][y].set_occupied(name);
	theBoard[x][y].notifyDisplay(td,gd);
}

void Board::remove(int x, int y){
	theBoard[x][y].setX(x);
	theBoard[x][y].setY(y);
	theBoard[x][y].set_occupied('Z');
	theBoard[x][y].notifyDisplay(td,gd);
}

bool Board::check_occupied(int x, int y){
	Cell* c = get_cell(x, y);
	if (c->get_occupied() == 'Z'){
		return false;
	}
	else{
		return true;
	}
}

std::ostream &operator<<(std::ostream &out, const Board &g){
	out << *g.td;
	return out;
}




