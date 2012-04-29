//Lab 5 - Single Player and Multiplayer Games
//Name: Atalie Holman (aholman@go.wustl.edu) and Mason Allen (mrallen@wustl.edu) and Chris Lauber (clauber@wustl.edu)
// 4-27-12
// Lab4.cpp : Defines the entry point for the console application.


#include "stdafx.h"
#include "abstractGame.h"
#include "nineAlmonds.h"
#include "magicSquares.h"

using namespace std;

// a usage function that tells the user options for correctly running the program
// it is called if the user specifies incorrect arguments from the console
endCondition usage()
{
	cout << "To run a game, please include its name as an argument after the program name." << endl;
	cout << "Game Options: NineAlmonds, MagicSquare, or Reversi" << endl ;
	cout << "Extra Arguments:" << endl;
	cout << "  NineAlmonds has none." << endl;
	cout << "  For Reversi, you must add 2 extra parameters for two player names." << endl;
	cout << "  For MagicSquare, you may add 1 or 2 optional extra parameters." << endl;
	cout << "    First, a size value that determines the board dimensions. (Default is 3)" << endl;
	cout << "    Second, a value that determines the lowest value number tile. (Default is 1)" << endl << endl;

	return USAGE;
}

// creates a pointer of abstract type that is specialized in the newGame function
int main(int argc, char* argv[])
{

	try
	{
		try
		{
			abstractGame :: self_->instance(argc, argv);
		}
		catch(endCondition)
		{
			cout << "There was an unknown error involving instancing." <<endl;
			return INSTANCEFAIL;
		}
	}
	catch(bad_alloc)
	{
		cout << "Failed to allocate memory." << endl;
	}

	if(abstractGame :: self_ == 0)
	{
		return usage();
	}

	try
	{
		endCondition play = abstractGame :: self_->play();
		delete abstractGame :: self_;
		return play;
	}
	catch(endCondition e)
	{	 
		if(e == QUIT)
		{
			abstractGame :: self_->isQuitting();
			cout << "Do you want to save? ";
			abstractGame :: self_->listen();
			delete abstractGame :: self_; 
			return QUIT;
		}
	}
}