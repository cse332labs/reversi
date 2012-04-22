#include "stdafx.h"

#ifndef ABSTRACTGAME_H
#define ABSTRACTGAME_H

#include "menus.h"
#include "Point.h"
#include "gamePiece.h"
//#include "nineAlmonds.h"
//#include "magicSquares.h"
#include "endCondition.h"
#include <vector>
#include <map>


using namespace std;

class abstractGame{

protected:
	typedef enum{SETUP, TURNSTART, FIRSTLOCKED, EXTENDEDTURN, ENDTURN, FINISHED}gameState;
	gameState state_;

	map<Point, gamePiece> board_;
	vector<map<Point, gamePiece>> undoBoards_;
	int boardx_, boardy_;
	int maxSymbol_;

	void pieceMover(Point start, Point destination);
	int getLength(int symbol); //didn't set this up right so that the derived classes would use this method; they use their own copies of the same method

public:
	abstractGame();

	abstractGame* newGame(int argc, char** argv);

	virtual void print()=0;
	virtual bool done()=0;
	virtual void prompt()=0;
	virtual void turn()=0;
	virtual endCondition play()=0;
	
};

#endif
