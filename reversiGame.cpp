//Lab 5 - Single Player and Multiplayer Games
//Name: Atalie Holman (aholman@go.wustl.edu) and Mason Allen (mrallen@wustl.edu) and Chris Lauber (clauber@wustl.edu)
// 4-27-12
// reversiGame.cpp

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
	reversiPiece black = reversiPiece(BLACK);
	reversiPiece white = reversiPiece(WHITE);

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
	bool noMoves = true;
	{
		for(int i = 0; i < boardx_; ++i)
		{
			for(int j = 0; j<boardy_; ++j)
			{
				if(checkMove(Point(i, j)))
				{
					noMoves = false;
				}
			}
		}
	}

	return noMoves;
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
		print();
		this->turn();
		if(this->done())
		{

			finished = true;
		}
	}

	//call new method here to update piece counts

	cout << "Game over. " << Bcount_ << " black pieces. " << Wcount_ << "white pieces." << endl;
	if(Bcount_ < Wcount_)
	{
		cout << playerW_ << " won! Congratulations!" <<endl;
	}
	else if(Wcount_ < Bcount_)
	{
		cout << playerB_ << " won! Congratulations!" <<endl;
	}
	else
	{
		cout << "Draw. " << endl;
	}
	cout << "Exiting game now." << endl << endl;
	return SUCCESS;
}

void reversiGame :: undo()
{
	return;
}


void reversiGame :: createSave()
{
	ofstream save;

	save.open(name_ + ".txt");

	bool finished = false;
	int line = 1;

	while(!finished)
	{
		switch(line)
		{
		case 1:
			save << "Reversi";
			break;
		case 2:
			save << name_;
			break;
		case 3:
			save << turn_ << " " << state_ << " " << boardx_ <<","<<boardy_;
			break;
		case 4:
			save << dest_.x_ << "," << dest_.y_;
			break;
		case 5:
			save << "START";
			break;
		default:
			for(int i = 0; i < boardx_; ++i)
			{
				for(int j = 0; j < boardy_; ++j)
				{
					Point temp = Point(i,j);
					if(board_.count(temp)==1)
					{
						reversiPiece piece = reversiPiece(board_.at(temp).color_);

						save << i << "," << j << " " << piece.symbol_ << endl;
						++line;
					}
				}
			}
			save << "END";
			finished=true;
			break;
		}
		save << endl;
		++line;
	}
}

void reversiGame :: loadSave()
{
	abstractGame :: loadSave("reversi");
}

//returns if there are any available moves from the given 
bool reversiGame:: checkMove(Point p)
{
	vector<Point> up, upright, right, downright, down, downleft, left, upleft;

	
	for(int offset = 0; offset < boardx_; ++offset)
	{
		if(board_.count(Point(p.x_, p.y_+offset))==1)
		{
			up.push_back(Point(p.x_, p.y_+offset));
		}
		if(board_.count(Point(p.x_+offset, p.y_+offset))==1)
		{
			upright.push_back(Point(p.x_+offset, p.y_+offset));
		}
		if(board_.count(Point(p.x_+offset, p.y_))==1)
		{
			right.push_back(Point(p.x_+offset, p.y_));
		}
		if(board_.count(Point(p.x_+offset, p.y_-offset))==1)
		{
			downright.push_back(Point(p.x_+offset, p.y_-offset));
		}
		if(board_.count(Point(p.x_, p.y_-offset))==1)
		{
			down.push_back(Point(p.x_, p.y_-offset));
		}
		if(board_.count(Point(p.x_-offset, p.y_-offset))==1)
		{
			downleft.push_back(Point(p.x_-offset, p.y_ - offset));
		}
		if(board_.count(Point(p.x_-offset, p.y_))==1)
		{
			left.push_back(Point(p.x_-offset, p.y_));
		}
		if(board_.count(Point(p.x_-offset, p.y_+offset))==1)
		{
			upleft.push_back(Point(p.x_-offset, p.y_+offset));
		}
	}

	bool ub = lineCheck(up);
	bool urb = lineCheck(upright);
	bool rb = lineCheck(right);
	bool drb = lineCheck(downright);
	bool d = lineCheck(down);
	bool dl = lineCheck(downleft);
	bool l = lineCheck(left);
	bool ul = lineCheck(upleft);
	
	if(ub || urb || rb || drb || d || dl || l || ul)
	{
		return true;
	}
	else
		return false;
}

bool reversiGame :: lineCheck(vector<Point> points)
{
	int size = points.size();
	pieceColor current;

	if(state_==BLACKTURN)
	{
		current = BLACK;
	}
	else
		current = WHITE;
	
	bool stillWorking = true, valid = false;

	int i = 0;
	while(stillWorking)
	{
		Point temp = points.at(i);
		if(board_.count(temp)==0 || i == size || temp.x_ >= boardx_ || temp.y_ >= boardy_)
		{
			stillWorking = false;
		}
		else
		{
			if(board_.at(temp).color_ != current)
			{
				++i;
			}
			else
			{
				if(i != 0)
				{
					valid = true;
				}
				stillWorking = false;
			}
		}
	}

	return valid;
}

bool reversiGame::addPiece()
{
	if(checkMove(dest_))
	{
		if(BLACKTURN)
		{
			reversiPiece black = reversiPiece(BLACK);
			board_[dest_] = black;
			pieceFlipper(dest_);
			return true;
		}
		else if(WHITETURN)
		{
			reversiPiece white = reversiPiece(WHITE);
			board_[dest_] = white;
			pieceFlipper(dest_);
			return true;
		}
		else
			return false;
	}
	else
	{
		return false;
	}
}

void reversiGame :: pieceFlipper(Point p)
{
	vector<Point> up, upright, right, downright, down, downleft, left, upleft;

	for(int offset = 0; offset < boardx_; ++offset)
	{
		if(board_.count(Point(p.x_, p.y_+offset))==1)
		{
			up.push_back(Point(p.x_, p.y_+offset));
		}
		if(board_.count(Point(p.x_+offset, p.y_+offset))==1)
		{
			upright.push_back(Point(p.x_+offset, p.y_+offset));
		}
		if(board_.count(Point(p.x_+offset, p.y_))==1)
		{
			right.push_back(Point(p.x_+offset, p.y_));
		}
		if(board_.count(Point(p.x_+offset, p.y_-offset))==1)
		{
			downright.push_back(Point(p.x_+offset, p.y_-offset));
		}
		if(board_.count(Point(p.x_, p.y_-offset))==1)
		{
			down.push_back(Point(p.x_, p.y_-offset));
		}
		if(board_.count(Point(p.x_-offset, p.y_-offset))==1)
		{
			downleft.push_back(Point(p.x_-offset, p.y_ - offset));
		}
		if(board_.count(Point(p.x_-offset, p.y_))==1)
		{
			left.push_back(Point(p.x_-offset, p.y_));
		}
		if(board_.count(Point(p.x_-offset, p.y_+offset))==1)
		{
			upleft.push_back(Point(p.x_-offset, p.y_+offset));
		}
	}

	lineFlipper(up);
	lineFlipper(upright);
	lineFlipper(right);
	lineFlipper(downright);
	lineFlipper(down);
	lineFlipper(downleft);
	lineFlipper(left);
	lineFlipper(upleft);
}

void reversiGame :: lineFlipper(vector<Point> points)
{
	int size = points.size();
	pieceColor current;

	if(state_==BLACKTURN)
	{
		current = BLACK;
	}
	else
		current = WHITE;

	vector<Point> toFlip;
	
	bool stillWorking = true, valid = false;

	int i = 0;
	while(stillWorking)
	{
		Point temp = points.at(i);
		if(board_.count(temp)==0 || i >= size || temp.x_ >= boardx_ || temp.y_ >= boardy_)
		{
			stillWorking = false;
		}
		else
		{

			if(board_.at(temp).color_ == current)
			{
				++i;
				toFlip.push_back(points.at(i));
			}
			else
			{
				stillWorking = false;
				valid = true;
			}
		}
	}

	if(valid)
	{
		for(unsigned int i = 0; i < toFlip.size(); ++i)
		{
			board_.at(toFlip.at(i)).flip();
		}
	}
}