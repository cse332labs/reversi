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
protected:
	static const string player1_;
	static const string player2_;
public:
	reversiGame();
	virtual void print();

};

#endif