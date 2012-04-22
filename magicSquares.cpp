#include "stdafx.h"
#include "magicSquares.h"
#include <sstream>

using namespace std;

magicSquare::magicSquare()
	: abstractGame()
{
	numberSquare number = numberSquare(1);
	setMax(maxSymbol_, boardx_);
}

void setMax(int & max, int boardLength)
{
	max = boardLength * boardLength; //the largest int in an nxn board
	string maxStr = "";
	stringstream intToStr;
	intToStr << max;
	intToStr >> maxStr;
	max = maxStr.size();

}

int getLengthMS(int symbol)
{
	string symbolStr = "";
	stringstream intToStr;
	intToStr << symbol;
	intToStr >> symbolStr;
	return symbolStr.size();
}


void magicSquare :: print()
{
	cout << *this << endl;
}

bool magicSquare :: done()
{
	return false;
}

void magicSquare :: prompt()
{

}

void magicSquare :: turn()
{

}

endCondition magicSquare :: play()
{
	return SUCCESS;
}


// the required operator overload that takes in a game object and prints out the board (and returns the stream).
// works for NxN boards :-)
ostream& operator<<(ostream &stream, const magicSquare &game)
{
	// formatting set-up to account for variable length symbols and for readability 
	char space = ' ';
	string spacing(game.maxSymbol_, space); // adds space the width of the max length symbol
	int dashCount = (game.boardx_ * (game.maxSymbol_ + 2)) + (game.boardx_ - 1); 
	string dashes(dashCount,'-');
	char verticalBar = '|';
	string dashRow = " ";
		dashRow += verticalBar + dashes + verticalBar;

	int piece = 0; //temp - pieces structure hasn't been created yet

	for(unsigned int y=(game.boardy_); y > 0; --y)
	{
		stream << dashRow << endl; //add a dashed line before each line of content for formatting

		for(int x=0; x < game.boardx_; ++x)
		{
			stream << space << verticalBar << space;
			if(game.board_.count(Point(x, y-1)) == 1) //is there a piece at that position?
			{
				if (getLengthMS(piece) < game.maxSymbol_) 
					//NOTE: using a temp var piece instead of getting the correct number (from the map?)
					// change to something like getLength(game.board_.at(Point(x, y-1)).value_ < game.maxSymbol_) ?
				{
				//determine number spaces to add before symbol
					string spaces(game.maxSymbol_ - getLengthMS(piece), space);
					stream << spaces;
				}
				stream << piece;
			}
			else
			{
				stream << spacing; 
			}
		}
		stream << space << verticalBar << endl;
	}
	stream << dashRow << endl << endl;
	stream << " Available Pieces: " << endl << endl; //add this in when we have the structure to keep track of unused pieces
	return stream;
}