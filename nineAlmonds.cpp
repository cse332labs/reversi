#include "stdafx.h"
#include "nineAlmonds.h"
#include <sstream>

using namespace std;

const unsigned int horizontal_dimension = 5;
const unsigned int vertical_dimension = 5;

nineAlmonds::nineAlmonds()
	: abstractGame(), turns_(0) //, boardx_(horizontal_dimension), boardy_(vertical_dimension)
{
	boardx_= horizontal_dimension;
	boardy_= vertical_dimension;
	almondPiece almond = almondPiece();
	for(int i=0; i < boardx_ ; ++i)
	{
		for(int j=0; j < boardy_; ++j)
		{
			//TODO: switch to generic values based on boardx_ and boardy_
			if( ((i<4)&&(i>0)) && ((j<4)&&(j>0)) )
			{
				Point temp = Point(i, j);
				board_[temp]=almond;
			}
		}
	}
	
	setMaxNA(maxSymbol_, boardx_);
	//maxSymbol_ = 1; //this is not a necessary variable for nine almonds if we only play it for a 5 x 5 board - factor out?
}

//this is used pretty much for magic squares
void setMaxNA(int & max, int boardLength)
{
	max = boardLength * boardLength; //NOTE: this is the max in an nxn board for magic squares; the largest in nine almonds would be boardLength
	string maxStr = "";
	stringstream intToStr;
	intToStr << max;
	intToStr >> maxStr;
	max = maxStr.size();

}

Point nineAlmonds::jumpedPiece(Point start, Point end)
{
	int jumpedx, jumpedy;

	jumpedx=(start.x_ + end.x_)/2;
	jumpedy=(start.x_ + end.y_)/2;
	return Point(jumpedx, jumpedy);
}

void nineAlmonds :: print()
{
	cout << *this << endl;
}

bool nineAlmonds :: done()
{
	return false;
}

void nineAlmonds :: prompt()
{

}

void nineAlmonds :: turn()
{

}

endCondition nineAlmonds :: play()
{
	return SUCCESS;
}




//not going to be necessary if we just use a 5x5 board but I left it in for testing the magic square board from here
int getLengthNA(int symbol)
{
	string symbolStr = "";
	stringstream intToStr;
	intToStr << symbol;
	intToStr >> symbolStr;
	return symbolStr.size();
}

/*
//
// UNCOMMENT THIS METHOD TO SEE THE MAGIC SQUARE BOARD (tested with the nineAlmonds game object)
//

// the required operator overload that takes in a game object and prints out the board (and returns the stream).
ostream& operator<<(ostream &stream, const nineAlmonds &game)
{
	// formatting set-up to account for variable length symbols and for readability 
	char space = ' ';
	string spacing(game.maxSymbol_, space); // adds space the width of the max length symbol
	char verticalBar = '|';
	int dashCount = (game.boardx_ * (game.maxSymbol_ + 2)) + (game.boardx_ - 1); 
	string dashes(dashCount,'-');
	string dashRow = " ";
		dashRow += verticalBar + dashes + verticalBar;
	int piece = 0; //temp - not sure what the pieces structure is

	for(unsigned int y=(game.boardy_); y > 0; --y)
	{
		stream << dashRow << endl; //add a dashed line before each line of content for formatting

		for(int x=0; x < game.boardx_; ++x)
		{
			stream << space << verticalBar << space;
			if(game.board_.count(Point(x, y-1)) == 1) //is there a piece at that position?
			{
				if (getLengthNA(piece) < game.maxSymbol_)
				{
				//determine number spaces to add before symbol
					string spaces(game.maxSymbol_ - getLengthNA(piece), space);
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
	stream << " Available Pieces: " << endl << endl; //add this in when we have the structure to hold pieces
	return stream;
}
*/

//
// This is the real operator for Nine Almonds
// The one above is a copy of the one in Magic Squares for testing
//
ostream& operator<<(ostream &stream, const nineAlmonds &game)
{
	// formatting set-up to account for variable length symbols and readability 
	char space = ' ';
	string spacing(game.maxSymbol_, space); // adds space the width of the max length symbol
	char verticalBar = '|';
	int dashCount = (game.boardx_ * 3) + (game.boardx_ - 1); 
	string dashes(dashCount,'-');
	string offset = spacing + space; // offets by the width of the vertical axis: "  |"
	string dashRow = offset + verticalBar + dashes + verticalBar;

	stream << space << 'y' << endl;
	for(unsigned int y=(game.boardy_); y > 0; --y)
	{
		stream << dashRow << endl; //add a dashed line before each line of content for formatting
		for(int x=0; x <= game.boardx_; ++x)
		{
			if(x==0 && y!=0)
			{
				if (getLengthNA(y-1) < game.maxSymbol_)
				{
				//determine number spaces to add before y-axis symbol (only need if we are using nxn boards)
					string spaces(game.maxSymbol_ - getLengthNA(y-1), space);
					stream << spaces;
				}
				stream << y-1; //prints vertical axis
			}
			else if(game.board_.count(Point(x-1, y-1)) == 1) //is there a piece at that position?
			{
				stream << 'A';
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