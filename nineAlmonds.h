#include "stdafx.h"

#ifndef NINEALMONDS_H
#define NINEALMONDS_H

#include "abstractGame.h"

using namespace std; 

class nineAlmonds : protected abstractGame {
	friend ostream& operator<<(ostream&, const nineAlmonds&);
private:
	bool validFirst_;
	bool extendedTurn_;
	unsigned int turns_;
	vector<Point> movesThisTurn_;
	void pieceKiller(Point p);

public:
	nineAlmonds();

	Point jumpedPiece(Point start, Point end);

	void print();
	bool done();
	void prompt();
	void turn();
	endCondition play();
};

void setMaxNA(int & max, int boardLength); //for testing of magic squares from nine almonds
int getLengthNA(int symbol); // should inherit a method from the base class instead of declaring one here

#endif