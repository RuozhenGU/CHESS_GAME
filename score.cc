#include "score.h"
#include <string>
#include <cmath>

using namespace std;

const string finalScore = "Final Score:\n";
const string whiteScore = "White: ";
const string blackScore = "Black: "; 

double Score::getWhite() { return white; }
	
double Score::getBlack() { return black; }

	
void Score::setWhite(double score) { white += score; }
	
void Score::setBlack(double score) { black += score; }
	
string Score::printScore() { 
	return finalScore + whiteScore + to_string(round(white*10)/10) + "\n" \
		+ blackScore + to_string(round(black*10)/10) + "\n";
}



