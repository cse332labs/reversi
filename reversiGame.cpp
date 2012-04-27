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

	Point ul = Point(3, 4);
	Point ur = Point(4, 4);
	Point ll = Point(3, 3);
	Point lr = Point(4, 3);
	board_[ul]=black;
	board_[lr]=black;
	board_[ur]=white;
	board_[ll]=white;
	


}

reversiGame::reversiGame(string playerB, string playerW)
	:abstractGame() 
{
	playerB_ = playerB;
	playerW_ = playerW;
}

// sets the board dimensions. 
void reversiGame :: setBoardDim(int n)
{
	boardx_=n;
	boardy_=n;
}

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

void reversiGame :: print()
{
	cout << *this << endl;
}

bool reversiGame :: done()
{
	//bool isFull = true;
	bool sameColor = false;

	Bcount_=0;
	Wcount_=0;

	Point key = Point();
	for(int i = 0; i < boardx_; ++i)
	{
		for (int j=0; j< boardy_; ++j)
		{
			key.set(i, j);
			if(board_.at(key).value_ == BLACK)
			{
				++Bcount_;
			}else if(board_.at(key).value_ == WHITE)
			{
				++Wcount_;
			}


		}
	}
	if((Bcount_+Wcount_ == 64) || (Bcount_>0 && Wcount_==0) || (Bcount_==0 && Wcount_>0) /* OR NO MOVES LEFT*/)  // fix so not hard coding
	{
		print();
		return true;
	}
	return false;
}


// calls prompt from abstractGame for now
void reversiGame :: prompt()
{
	switch(state_)
	{
	case WHITETURN:
		cout << playerW_ << " select a piece to move? ";
		break;
	case BLACKTURN:
		cout << playerB_ << " select a piece to move? ";
		break;
	case NEEDPIECE:
		cout << "That move was not valid." << endl;
		break;
	}
}

void reversiGame :: turn()
{
	prompt();
	listen();
	if(addPiece())
	{
		if(state_=WHITETURN)
		{
			state_=BLACKTURN;
			++turn_;
		}
		else
		{
			state_=WHITETURN;
		}
	}
	else
	{
		gameState temp = state_;
		state_ = NEEDPIECE;
		prompt();
		state_ = temp;
		return;
	}
}

endCondition reversiGame :: play()
{
	bool finished = false;
	while(!finished)
	{
		this->turn();
		if(this->done())
		{

			finished = true;
		}
	}

	cout << "Congratulations! You completed the game! Exiting game now." << endl << endl;
	return SUCCESS;
}



//abstract version of undo(), retreives most recent piece from usedPieces_ (i.e. the most recent move)
// and calls undo(numberSquare piece) on it (below)
void reversiGame :: undo()
{
}


void reversiGame :: createSave()
{
}

void reversiGame :: loadSave()
{
	abstractGame :: loadSave("reversigame");
}

bool reversiGame:: checkMove()
{
	bool firstCheck = false;
	int offset = 1;
	for(int i = dest_.y_+1; i < boardy_; ++ i)
	{
		Point temp = Point(dest_.x_, i);
	}
	return false;
}

bool reversiGame::addPiece()
{
	return true;
}