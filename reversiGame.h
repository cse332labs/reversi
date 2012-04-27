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
private:
	static const string playerB_;
	static const string playerW_;
public:
	reversiGame();

	// sets the board dimensions
	virtual void setBoardDim(int n);

	virtual void prompt();
	virtual void print();
	virtual bool done();

};

#endif