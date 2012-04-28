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
	cout << "To run this program, please include the name of the game you wish to run as an argument" << endl;
	cout << "Game Options: NineAlmonds or MagicSquare" << endl;
	cout << "For MagicSquare, you may add 1 or 2 optional extra parameters." << endl;
	cout << "First, a size value may be specified that determines the board dimensions." << endl;
	cout << "The second extra value determines the lowest value of the number tiles." << endl;
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
			cout << "There was an uknown error involving instancing." <<endl;
			return INSTANCEFAIL;
		}
	}
	catch(bad_alloc)
	{
		cout << "Failed to allocate memory." << endl;
	}

	if(abstractGame :: self_ != 0)
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

