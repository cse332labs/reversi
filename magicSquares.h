//Lab 4 - Nine Almonds and Magic Squares
//Name: Atalie Holman (aholman@go.wustl.edu) and Mason Allen (mrallen@wustl.edu)
// 5-7-12
// magicSquares.h

#include "stdafx.h"

#ifndef MAGICSQUARES_H
#define MAGICSQUARES_H

#include "abstractGame.h"
#include <algorithm>


using namespace std;

// class of Magicsquares game
class magicSquares : public abstractGame {
	friend ostream& operator<<(ostream &stream, const magicSquares &game);
	friend ostream& operator<<(ostream &stream, const vector<numberSquare> &pieces);
	friend void abstractGame :: loadSquares(string name);
protected:
	// tile selected by player
	unsigned int chosenTile_;
	int lowest_;

	// available tiles and used pieces (used for undo)
	vector<numberSquare> availablePieces_;
	vector<numberSquare> usedPieces_;
	
	// similar to maxSymbol, ensures y axis labels are right by storing maxAxis value length
	unsigned int maxAxis_;
	
	// puts piece at point P
	void pieceAdd(numberSquare &piece, Point p);

	// sets the board dimensions
	void setBoardDim(int n);

	// finds the magic constant value for this game
	int getMagicConstant();

	//helper methods used in done()
	int sumRow(int r);
	int sumCol(int c);

	//calls undo(numberSquare piece) for the most recent move
	virtual void undo();
	//takes piece off the board and makes it available again. increments turn_
	virtual void undo(numberSquare piece);

	virtual void createSave();
	virtual void loadSave();

	void generateTiles(int lowest, int dim);

	bool checkTile(int value);

public:
	magicSquares();
	magicSquares(int size);
	magicSquares(int size, int lowest);

	virtual void print();
	virtual bool done();
	virtual void prompt();
	virtual void prompt(unsigned int &numberTile);
	virtual void turn();
	virtual void listen();
	virtual void listen(unsigned int &numberTile);
	virtual endCondition play();



};
#endif