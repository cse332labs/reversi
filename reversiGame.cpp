//Lab 5 - Single Player and Multiplayer Games
//Name: Atalie Holman (aholman@go.wustl.edu) and Mason Allen (mrallen@wustl.edu) and Chris Lauber (clauber@wustl.edu)
// 4-27-12
// reversiGame.cpp

#include "stdafx.h"
#include "reversiGame.h"
#include <iostream>

using namespace std;



//constructs reversiGame using the base class constructor and its own specifications. fills board
// for proper reversi game.
reversiGame :: reversiGame()
{
	string playerW, playerB;
	getNames(playerB, playerW);
	reversiGame(playerB, playerW);
}

reversiGame :: reversiGame(string playerB, string playerW)
	:abstractGame(), needPoint_(false)
{
	this->setBoardDim(defaultBoardSize);

	maxSymbol_=1;

	playerB_ = playerB;
	playerW_ = playerW;

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
	stream << offset;  // offsets the axis labeling by the width of the vertical axis

	//prints the horizontal axis
	for(int xPos=0; xPos < game.boardx_; ++xPos)
	{
		stream << space << space << xPos << space;
	}
	stream << " x" << endl;
	return stream;
}

//prints the board state using the ostream insertion operator
void reversiGame :: print()
{
	cout << *this << endl;
}


//this method checks to see if the game termination conditions have been met
//conditions: board is full, all pieces are one color, or no valid moves remain
bool reversiGame :: done()
{
	//bool isFull = true;
	/*
	bool sameColor = false;

	Bcount_=0;
	Wcount_=0;

	Point key = Point();
	for(int i = 0; i < boardx_; ++i)
	{
		for (int j=0; j< boardy_; ++j)
		{
			key.set(i, j);
			if(board_.count(key) == 1)
			{
				if(board_.at(key).value_ == BLACK)
				{
					++Bcount_;
				}
				else if(board_.at(key).value_ == WHITE)
				{
					++Wcount_;
				}
			}
		}
	}
	if((Bcount_+Wcount_ == 64) || (Bcount_>0 && Wcount_==0) || (Bcount_==0 && Wcount_>0)) 
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
				if(board_.count(Point(i, j)) == 0)
				{
					cout << "Checking " << i << " " << j << endl;
					Point temp = Point(i, j);
					if(checkMove(temp))
					{
						noMoves = false;
					}
				}
			}
		}
	}

	return noMoves;
	*/
	return false;
}


void reversiGame :: prompt()
{

	switch(state_)
	{
	case WHITETURN:
		cout << playerW_ << ", where do you want to place your piece this turn? ";
		needPoint_ = true;
		break;
	case BLACKTURN:
		cout << playerB_ << ", where do you want to place your piece this turn? ";
		needPoint_ = true;
		break;
	case NEEDPIECE:
		cout << "That move was not valid." << endl;
		break;
	}
}

void reversiGame :: turn()
{
	print();
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
	state_ = BLACKTURN;
	while(!finished)
	{
		turn();
		if(done())
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

void reversiGame::countALLtheThings()
{
	Bcount_ = 0;
	Wcount_ = 0;
	for(int i = 0; i < boardx_; ++i)
	{
		for(int j = 0; j < boardy_; ++j)
		{
			Point temp = Point(i,j);
			reversiPiece piece = reversiPiece(board_.at(temp).color_);
			if(piece.color_==BLACK)
			{
				++Bcount_;
			}else if(piece.color_ == WHITE){
				++Wcount_;
			}else{
				return;
			}
		}
	}
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

	bool ub=false, urb=false, rb=false, drb=false, db=false, dlb=false, lb=false, ulb=false;


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

	if(!(up.size() == 0))
	{
		ub = lineCheck(up);
	}
	if(!(up.size()) == 0)
	{
		urb = lineCheck(upright);
	}
	if(!(right.size()) == 0)
	{
		rb = lineCheck(right);
	}
	if(!(downright.size()) == 0)
	{
		drb = lineCheck(downright);
	}
	if(!(down.size()) == 0)
	{
		db = lineCheck(down);
	}
	if(!(downleft.size()) == 0)
	{
		dlb = lineCheck(downleft);
	}
	if(!(left.size()) == 0)
	{
		lb = lineCheck(left);
	}
	if(!(upleft.size()) == 0)
	{
		ulb = lineCheck(upleft);
	}

	if(ub || urb || rb || drb || db || dlb || lb || ulb)
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

	bool ub=false, urb=false, rb=false, drb=false, db=false, dlb=false, lb=false, ulb=false;


	for(int offset = 1; offset < boardx_; ++offset)
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

	if(!(up.size() == 0))
	{
		lineFlipper(up);
	}
	if(!(up.size()) == 0)
	{
		lineFlipper(upright);
	}
	if(!(right.size()) == 0)
	{
		lineFlipper(right);
	}
	if(!(downright.size()) == 0)
	{
		lineFlipper(downright);
	}
	if(!(down.size()) == 0)
	{
		lineFlipper(down);
	}
	if(!(downleft.size()) == 0)
	{
		lineFlipper(downleft);
	}
	if(!(left.size()) == 0)
	{
		lineFlipper(left);
	}
	if(!(upleft.size()) == 0)
	{
		lineFlipper(upleft);
	}
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
		Point temp;
		if(i < size)
		{
			temp = points.at(i);
		}
		else
		{
			stillWorking=false;
		}
		if(board_.count(temp)==0 || temp.x_ >= boardx_ || temp.y_ >= boardy_)
		{
			stillWorking = false;
		}
		if(stillWorking)
		{
			if(!(board_.at(temp).color_ == current))
			{
				toFlip.push_back(temp);
				++i;
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

void reversiGame :: listen()
{
	if(needPoint_)
	{
		listenForPoint();
		needPoint_ = false;
		return;
	}
	else
	{
		abstractGame :: listen();
	}
}

void reversiGame :: listenForPoint()
{
	gameState temp = state_;
	state_ = REVERSIPOINT;
	abstractGame :: listen();
	state_ = temp;
	return;
}

