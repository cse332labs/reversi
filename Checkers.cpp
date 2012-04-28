//Lab 5 - Single Player and Multiplayer Games
//Name: Atalie Holman (aholman@go.wustl.edu) and Mason Allen (mrallen@wustl.edu) and Chris Lauber (clauber@wustl.edu)
// 4-27-12
// Checkers.cpp

#include "stdafx.h"
#include "Checkers.h"
#include <iostream>

using namespace std;

const int defaultSize = 8;

//constructs reversiGame using the base class constructor and its own specifications. fills board
// for proper reversi game.
Checkers :: Checkers()
{
	string playerW, playerB;
	getNames(playerB, playerW);
	Checkers(playerB, playerW);
}

Checkers :: Checkers(string playerB, string playerW)
	:abstractGame()
{
}


ostream& operator<<(ostream &stream, const Checkers &game)
{
	// formatting set-up to account for variable length symbols and readability 
	char space = ' ';
	string spacing(game.maxSymbol_, space); // adds space the width of the max length symbol
	char verticalBar = '|';
	int dashCount = (game.boardx_ * 3) + (game.boardx_ - 1); 
	string dashes(dashCount,'-');
	string offset = spacing + space; // offets by the width of the vertical axis
	string dashRow = offset + verticalBar + dashes + verticalBar;

	stream << space << 'y' << endl;
	for(unsigned int y=(game.boardy_); y > 0; --y)
	{
		stream << dashRow << endl; //add a dashed line before each line of content for formatting
		for(int x=0; x <= game.boardx_; ++x)
		{
			if(x==0 && y!=0)
			{
				if (getLength(y-1) < game.maxSymbol_)
				{
					//determine number spaces to add before y-axis symbol (only need if we are using nxn boards)
					string spaces(game.maxSymbol_ - getLength(y-1), space);
					stream << spaces;
				}
				stream << y-1; //prints vertical axis
			}
			else if(game.board_.count(Point(x-1, y-1)) == 1) //check if there is a piece at that position
			{
				stream << game.board_.at(Point(x-1, y-1)).symbol_;
			}
			else
			{
				stream << space; 
			}
			stream << space << verticalBar << space;
		}
		stream << endl;
	}
	stream << dashRow << endl;
	stream << offset;  // offets the axis labeling by the width of the vertical axis

	//prints the horizontal axis
	for(int xPos=0; xPos < game.boardx_; ++xPos)
	{
		stream << space << space << xPos << space;
	}
	stream << " x" << endl;
	return stream;
}

void Checkers :: print()
{
	cout << *this << endl;
}

bool Checkers :: done()
{
	return false;
}

void Checkers :: turn()
{
	return;
}
endCondition Checkers :: play()
{
	return SUCCESS;
}

void Checkers :: createSave()
{
	return;
}

void Checkers :: loadSave()
{
	return;
}








//not needed but necessary functions below
void Checkers :: undo()
{
	return;
}