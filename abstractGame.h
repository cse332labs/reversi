//Lab 5 - Single Player and Multiplayer Games
//Name: Atalie Holman (aholman@go.wustl.edu) and Mason Allen (mrallen@wustl.edu) and Chris Lauber (clauber@wustl.edu)
// 4-27-12
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

const int defaultBoardSize = 8;

using namespace std;

	typedef enum{SETUP, TURNSTART, FIRSTLOCKED, NEEDPIECE, NEEDLOC, EXTENDEDTURN, ENDTURN, FINISHED, QUITTING, WHITETURN, BLACKTURN, REVERSIPOINT, PROCESSING, BADSTATE}gameState;


// struct of abstract (base) game type. Above are the various states that the game could be in declared in an enum
class abstractGame{
protected:
	// stores state
	static gameState state_;
	static gameType type_;

	static string roughType_, roughArg1_, roughArg2_;

	//stores game Name
	string name_;

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


	
	Point placeHolder_;
	virtual void undo()=0;

	virtual void createSave()=0;
	virtual void loadSave()=0;
	virtual void loadSave(string name);

	void loadAlmonds(string in);
	void loadSquares(string in);
	void loadReversi(string in);
	void loadCheckers(string in);

	void noSave();

	void nameChecker();

	gameState intToState(int i);

	//method that can return various types of sub-games
	static void newGame(int argc, abstractGame*& pointer);

	// used by magicSquares and reversiGame to set the board size
	virtual void setBoardDim(int n);

public:
	abstractGame();

	static abstractGame* self_;

	void setState(gameState s);

	static void instance(int argc, char* argv[]);

	void isQuitting();



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
