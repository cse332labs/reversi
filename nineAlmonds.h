//Lab 5 - Single Player and Multiplayer Games
//Name: Atalie Holman (aholman@go.wustl.edu) and Mason Allen (mrallen@wustl.edu) and Chris Lauber (clauber@wustl.edu)
// 4-27-12
// nineAlmonds.h

#include "stdafx.h"

#ifndef NINEALMONDS_H
#define NINEALMONDS_H

#include "abstractGame.h"
#include <vector>

using namespace std; 

class nineAlmonds : public abstractGame {
	friend ostream& operator<<(ostream&, const nineAlmonds&);
	friend void abstractGame :: loadAlmonds(string name);
private:
	// displays moves in ostringstream form
	ostringstream moves_;

	// stores original point for the turn
	Point original_;

	//finds the piece being jumped
	Point jumpedPiece(Point start, Point end);
	virtual bool pieceMover(Point start, Point destination);

	virtual void undo();

	virtual void createSave();
	void loadSave();

public:
	nineAlmonds();

	virtual void print();
	virtual bool done();
	virtual void prompt();
	virtual void turn();
	virtual void listen();
	virtual endCondition play();
};

#endif