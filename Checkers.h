//Lab 5 - Single Player and Multiplayer Games
//Name: Atalie Holman (aholman@go.wustl.edu) and Mason Allen (mrallen@wustl.edu) and Chris Lauber (clauber@wustl.edu)
// 4-27-12
// Checkers.h

#include "stdafx.h"

#ifndef CHECKERS_H
#define CHECKERS_H

#include "Point.h"
#include "gamePiece.h"
#include "endCondition.h"
#include "abstractGame.h"
#include "inputProcessing.h"
#include "Checkers.h"
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <map>

using namespace std;

typedef enum{EMPTY, UP, JUMPUP, DOWN, JUMPDOWN}moveType;

class Checkers : public abstractGame{
	friend ostream& operator<<(ostream &stream, const Checkers &game);
protected:
	string playerB_;
	string playerR_;

	bool isBlacksTurn_;

	Point original_, jumped_;

	static bool notFinished_;

	int Bcount_, Rcount_;

	moveType currentMoveType_;

	//uses the member variables start_ and dest_ to check if the move is valid. It does NOT
	// move the pieces, only check validity.
	bool moveCheck(Point start, Point dest);

	// returns true of the move from start to destination is valid. Also updates jumped_ 
	// member variable. DOES NOT DO THE MOVING
	bool jumpedPiece(Point start, Point dest);
	bool checkStartSelect();

	// this will move whatever is in start to whatever is in destination. 
	void movePiece();

	void removePiece(Point p);

	vector<Point> possibleLocations(Point p);

	moveType getMoveType(Point start, Point destination);

	virtual void undo();
	virtual void createSave();
	virtual void loadSave();

	bool 

	void listMoves();

	void movesOut(ostream& stream, vector<Point> points);
	
public:
	Checkers();
	Checkers(string playerB, string playerW);

	virtual void prompt();
	virtual void print();
	virtual bool done();
	virtual void turn();
	virtual void listen();
	virtual endCondition play();
};


#endif