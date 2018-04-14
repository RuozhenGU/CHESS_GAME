#include "textdisplay.h"
#include <iostream>

using namespace std;

TextDisplay::TextDisplay() {
	vector<vector<char>> v(boardSize, vector<char>(boardSize, '-'));
	for(int i=0; i < boardSize; ++i) {
		for(int j=0; j < boardSize; ++j) {
			if((i % 2 == 0 && j % 2 != 0) || (i % 2 != 0 && j % 2 == 0)) {
				v[i][j] = ' '; // white cell
			}
 		}
	}
	theDisplay = v;
}

void TextDisplay::notify(char cell, int x, int y) {
	if(cell == empty) {
		if((x % 2 == 0 && y % 2 != 0) || (x % 2 != 0 && y % 2 == 0)) {
				theDisplay[x][y] = ' '; // white cell
		}
		else {
			theDisplay[x][y] = '-'; // black cell
		}
	}
	else {
		theDisplay[x][y] = cell;
	}
}

ostream &operator<<(ostream &out, const TextDisplay &td) {
	out << endl;
	for(int i = boardSize-1; i >= 0; --i) {
		out << i+1 << ' ';
		for(int j = 0; j < boardSize; ++j) {
			out << td.theDisplay[j][i];
		}
		out << endl;
	}
	out << endl << "  abcdefgh" << endl << endl;
	return out;
}






