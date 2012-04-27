//Lab 4 - Nine Almonds and Magic Squares
//Name: Atalie Holman (aholman@go.wustl.edu) and Mason Allen (mrallen@wustl.edu)
// 5-7-12
// abstractGame.h

#include "stdafx.h"

#ifndef ABSTRACTGAME_H
#define ABSTRACTGAME_H

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

	typedef enum{SETUP, TURNSTART, FIRSTLOCKED, NEEDPIECE, NEEDLOC, EXTENDEDTURN, ENDTURN, FINISHED, QUITTING, WHITETURN, BLACKTURN, BADSTATE}gameState;

// struct of abstract (base) game type. Above are the various states that the game could be in declared in an enum

class abstractGame{
protected:
	// stores state
	gameState state_;

	//stores game Name
	string name_;

	abstractGame* self;

	//stores number of turns (nineAlmonds) or number of uses of undo (magicSquare)
	int turn_;

	//prevents accidental quitting
	bool quitGuard_, quitting_, comingBack_;

	// used for game logic
	bool validFirst_;

	// used to store points from user input
	Point start_;
	Point dest_;

	// the game board in memory
	map<Point, gamePiece> board_;

	//holds copies of the game board that can be used by undo
	vector<map<Point, gamePiece>> undoBoards_;

	//list of moves made this turn
	vector<Point> movesThisTurn_;

	// board dimensions
	int boardx_, boardy_;

	// for display purposes
	int maxSymbol_;

	//function to move piece from start to destination on board_
	virtual bool pieceMover(Point start, Point destination);
	static abstractGame* instance();

	
	Point placeHolder_;
	virtual void undo()=0;

	virtual void createSave()=0;
	virtual void loadSave()=0;
	virtual void loadSave(string name);

	void loadAlmonds(string in);
	void loadSquares(string in);
	void loadReversi(string in);

	void noSave();

	void nameChecker();

	gameState intToState(int i);

	// used by magicSquares and reversiGame to set the board size
	virtual void setBoardDim(int n);

public:
	abstractGame();

	void setState(gameState s);

	void isQuitting();

	//method that can return various types of sub-games
	abstractGame* newGame(int argc, char* argv[]);

	virtual void print()=0;
	virtual bool done()=0;
	virtual void prompt();
	virtual void turn()=0;
	virtual void listen();
	virtual gameState getState();
	virtual endCondition play()=0;

	int maxSymbol();

};

#endif
