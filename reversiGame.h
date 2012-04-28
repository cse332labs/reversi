//Lab 5 - Single Player and Multiplayer Games
//Name: Atalie Holman (aholman@go.wustl.edu) and Mason Allen (mrallen@wustl.edu) and Chris Lauber (clauber@wustl.edu)
// 4-27-12
// reversiGame.h

#include "stdafx.h"

#ifndef REVERSIGAME_H
#define REVERSIGAME_H

#include "abstractGame.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std; 

class reversiGame : public abstractGame {
	friend ostream& operator<<(ostream &stream, const reversiGame &game);
	friend void abstractGame :: loadReversi(string name);
protected:
	string playerB_;
	string playerW_;

	int Bcount_, Wcount_;

	bool checkMove(Point p);
	bool addPiece();

	void pieceFlipper(Point p);

	void lineFlipper(vector<Point> points);
	bool lineCheck(vector<Point> points);

	virtual void createSave();
	virtual void loadSave();
	
	//temporarily adding - we probably shouldn't give the option to undo but it is pure virtual in abstractGame
	virtual void undo();
public:
	reversiGame();
	reversiGame(string playerB, string playerW);

	// sets the board dimensions
	virtual void setBoardDim(int n);

	virtual void prompt();
	virtual void print();
	virtual bool done();
	virtual void turn();
	virtual endCondition play();
};

#endif