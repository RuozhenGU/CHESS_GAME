#ifndef CELL_H
#define CELL_H
#include <cstddef>
#include <memory>
class TextDisplay;
class GraphicalDisplay;


class Cell{
	char occupied;
	int x;
	int y;

public:
	Cell(char occ, int x, int y);
	char get_occupied();
	void set_occupied(char occ);
	bool isWhite();
	int getX();
	int getY();
	void setX(int x);
	void setY(int y);
	void notifyDisplay(std::shared_ptr<TextDisplay> td,std::shared_ptr<GraphicalDisplay> gd);
};
#endif


