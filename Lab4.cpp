// Lab4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "menus.h"
#include "abstractGame.h"
#include "nineAlmonds.h"
#include "magicSquares.h"

using namespace std;

void usage()
{

}

int main(int argc, char* argv[])
{

	//abstractGame* game = newGame(argc, argv);

	nineAlmonds almondGame;
	cout << almondGame;
	menu Menu = menu();

}

