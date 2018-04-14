#include "cell.h"
#include "textdisplay.h"
#include "graphicaldisplay.h"
#include "window.h"
#include <iostream>
#include <string>
using namespace std;
Cell::Cell(char occ, int x, int y) : occupied{ occ }, x{ x }, y{ y }{}
char Cell::get_occupied(){
	return this->occupied;
}
void Cell::set_occupied(char occ){
	this->occupied = occ;
}
int Cell::getX(){
	return this->x;
}
int Cell::getY(){
	return this->y;
}
void Cell::notifyDisplay(shared_ptr<TextDisplay> td, shared_ptr<GraphicalDisplay> gd){
	td->notify(occupied, x, y);
	gd->notify(occupied, x, y);
}

bool Cell::isWhite(){
	if ('A' <= occupied && occupied <= 'Z'){
		return true;
	}
	else{
		return false;
	}
}

void Cell::setX(int x){
	this->x = x;
}

void Cell::setY(int y){
	this->y = y;
}





