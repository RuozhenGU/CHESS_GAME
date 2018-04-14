#ifndef SCORE_H
#define SCORE_H
#include <string>

class Score {
	double white = 0;
	double black = 0;

public:
	double getWhite();
	double getBlack();
	void setWhite(double score);
	void setBlack(double score);
	std::string printScore();
};

#endif





