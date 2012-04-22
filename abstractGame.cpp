#include "stdafx.h"
#include "abstractGame.h"
#include "inputProcessing.h"
#include "nineAlmonds.h"
#include "magicSquares.h"
#include <sstream>

using namespace std;

abstractGame::abstractGame()
	: state_(SETUP) {}

abstractGame* abstractGame::newGame(int argc, char** argv)
{
	if(argc != 2)
	{
		return NULL;
	}
	string gameName = argv[1];
	lowerCase(gameName);
	if(gameName == "ninealmonds")
	{
		nineAlmonds* game = new nineAlmonds();
		return (abstractGame*) &game;
	}
	else if(gameName == "magicsquare")
	{
		magicSquare* game = new magicSquare();
		return (abstractGame*) &game;
	}
	else
	{
		return NULL;
	}
}

int getLength(int symbol)
{
	string symbolStr = "";
	stringstream intToStr;
	intToStr << symbol;
	intToStr >> symbolStr;
	return symbolStr.size();
}
