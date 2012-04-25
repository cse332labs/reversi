#include "stdafx.h"

#ifndef REVERSIGAME_H
#define REVERSIGAME_H

#include "abstractGame.h"
#include <vector>

using namespace std; 

class reversiGame : public abstractGame {
	friend ostream& operator<<(ostream &stream, const reversiGame &game);
private:
	static string player1 = "";
	static string player2 = "";
public:
	reversiGame();
	virtual void print();

}

#endif