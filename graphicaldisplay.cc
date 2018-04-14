#include "graphicaldisplay.h"
#include "window.h"
#include <string>

using namespace std;

GraphicalDisplay::GraphicalDisplay(){

for(int i = 8; i>0;--i){
	xw.drawString(10, -20+i*60, to_string(9-i), xw.Black);
}
for(int i = 8; i>0;--i){
	char c = i-1+'a';
	xw.drawString(i*60+5, 510, string(1, c), xw.Black);
	
}

	
	xw.fillRectangle(35, 0, 5, 485, xw.Black);
	xw.fillRectangle(40, 480, 480, 5, xw.Black);

	for(int i = 0; i<8;++i){
		for(int j=0;j<8;++j){
			if((j % 2 == 0 && i % 2 != 0) || (j % 2 != 0 && i % 2 == 0)) {
				xw.fillRectangle(j*60+40, i*60, 60, 60, xw.Black); // black cell
			}else{
				xw.fillRectangle(j*60+40, i*60, 60, 60, xw.White); // white cell
			}
		}
	}

}

void GraphicalDisplay::notify(char cell, int x, int y){
	if(cell == 'Z') {
		if((x % 2 == 0 && y % 2 != 0) || (x % 2 != 0 && y % 2 == 0)) {
			xw.fillRectangle(40+60*x, 480-60*(y+1), 60, 60, xw.White); // white cell
		}
		else {
			xw.fillRectangle(40+60*x, 480-60*(1+y), 60, 60, xw.Black); // black cell
		}
	}
	else {
		if((x % 2 == 0 && y % 2 != 0) || (x % 2 != 0 && y % 2 == 0)) {
			xw.fillRectangle(40+60*x, 480-60*(y+1), 60, 60, xw.White); // white cell
			xw.drawBigString(40+60*x+15, 480-60*y-15, string(1,cell), xw.Orange);
		}
		else {
			xw.fillRectangle(40+60*x, 480-60*(1+y), 60, 60, xw.Black); // black cell
			xw.drawBigString(40+60*x+15, 480-60*y-15, string(1,cell), xw.Orange);
		}
		
	}
}



