#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>
#include <cstddef>
#include <memory>

class Cell;
class TextDisplay;
class GraphicalDisplay;


class Board {
	std::vector<std::vector<Cell>> theBoard;  // The actual board.
    std::shared_ptr<TextDisplay> td; // The text display.
    std::shared_ptr<GraphicalDisplay> gd; 
public:
	Board();
	Cell* get_cell(int x, int y);
	void init(); // Sets up board.  Clears old board, if necessary.
    void initsetup(); //when restart the game, use this to re-init the boards
	void place(char name, int x, int y);
	void remove(int x, int y);
	bool check_occupied(int x, int y);
	friend std::ostream &operator<<(std::ostream &out, const Board &g);

};
#endif




