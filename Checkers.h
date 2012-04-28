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
#include "inputProcessing.h"
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <map>

using namespace std;

class Checkers: public abstractGame{
	friend ostream& operator<<(ostream &stream, const Checkers &game);
protected:
	virtual void undo();
	virtual void createSave();
	virtual void loadSave();
	
public:
	Checkers();
	Checkers(string playerB, string playerW);

	virtual void print();
	virtual bool done();
	virtual void turn();
	virtual endCondition play();
};


#endif