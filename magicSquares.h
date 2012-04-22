#include "stdafx.h"

#ifndef MAGICSQUARES_H
#define MAGICSQUARES_H

#include "abstractGame.h"

using namespace std;

class magicSquare : abstractGame {
	friend ostream& operator<<(ostream&, const magicSquare&);
public:
	magicSquare();
	virtual void print();
	virtual bool done();
	virtual void prompt();
	virtual void turn();
	virtual endCondition play();
};

void setMax(int & max, int boardLength);
int getLengthMS(int symbol); //shouldn't be here, want to use a base class version instead unless method isn't needed in nine almonds later

#endif