#include "stdafx.h"
#include "reversiGame.h"
#include <iostream>

using namespace std;

const int defaultSize = 8;

//constructs reversiGame using the base class constructor and its own specifications. fills board
// for proper reversi game.
reversiGame::reversiGame()
	:abstractGame()
{
	this->setBoardDim(defaultSize);

	//define initial pieces
	reversiPiece black = reversiPiece();
	reversiPiece white = reversiPiece(false);
	Point ll = Point(3, 3);
	Point lr = Point(3, 4);
	Point ul = Point(3, 4);
	Point ur = Point(4, 4);
	board_[ll]=white;
	board_[lr]=black;
	board_[ul]=white;
	board_[ur]=black;


}

// sets the board dimensions. 
void reversiGame :: setBoardDim(int n)
{
	boardx_=n;
	boardy_=n;
}

// calls prompt from abstractGame
void reversiGame :: prompt()
{
	abstractGame :: prompt();

ostream& operator<<(ostream &stream, const reversiGame &game)
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
                                reversiPiece reverse = reversiPiece();
								stream << reverse.symbol_;
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
        stream << " x" << endl;
        //prints the horizontal axis
        for(int xPos=0; xPos < game.boardx_; ++xPos)
        {
                stream << space << space << xPos << space;
        }

        return stream;
}

void reversiGame :: print()
{
	cout << *this << endl;
}

bool reversiGame :: done()
{
	//bool isFull = true;
	bool sameColor = false;
	int Bcount = 0;
	int Wcount = 0;
	Point key = Point();
	for(int i = 0; i < boardx_; ++i)
	{
		for (int j=0; j< boardy_; ++j)
		{
			key.set(i, j);
			if(board_.at(key).value_ == BLACK)
			{
				++Bcount;
			}else if(board_.at(key).value_ == WHITE)
			{
				++Wcount;
			}


		}
	}
	if((Bcount+Wcount == 64) || (Bcount>0 && Wcount==0) || (Bcount==0 && Wcount>0) /* OR NO MOVES LEFT*/)  // fix so not hard coding
	{
		print();
		return true;
	}
	return false;
}

void reversiGame :: prompt()
{
	abstractGame :: prompt();
}

void reversiGame :: turn()
{
	bool isBlackTurn = true;
	switch(state_)
	{
		case SETUP:
			cout << "Welcome to Nine Almonds!" << endl;
			cout << "Your goal is to remove all almonds except for one, leaving the final almond in the center square (2,2)." << endl;
			cout << "You may make moves by jumping one almond over another, removing the jumped piece. Use a square's coordinate point to select it."<< endl;
			state_=TURNSTART;
			break;
		
	}
	
	isBlackTurn = !isBlackTurn;
	print();
	prompt();
	listen();

}