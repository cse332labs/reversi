//Lab 4 - Nine Almonds and Magic Squares
//Name: Atalie Holman (aholman@go.wustl.edu) and Mason Allen (mrallen@wustl.edu)
// 5-7-12
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
	abstractGame* game = 0;

	try
	{
		try
		{
			game->instance(argc, argv);
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

	if(!game)
	{
		return usage();
	}

	try
	{
		endCondition play = game->play();
		delete game;
		return play;
	}
	catch(endCondition e)
	{	 
		if(e == QUIT)
		{
			game->isQuitting();
			cout << "Do you want to save? ";
			game->listen();
			delete game; 
			return QUIT;
		}
	}
}

