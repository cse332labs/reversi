//Lab 5 - Single Player and Multiplayer Games
//Name: Atalie Holman (aholman@go.wustl.edu) and Mason Allen (mrallen@wustl.edu) and Chris Lauber (clauber@wustl.edu)
// 4-27-12
// Checkers.cpp

#include "stdafx.h"
#include "Checkers.h"
#include <iostream>

using namespace std;

bool Checkers :: notFinished_ = true;

//constructs reversiGame using the base class constructor and its own specifications. fills board
// for proper reversi game.
Checkers :: Checkers()
{
	string playerR=" ", playerB=" ";
	Checkers(playerB, playerR);
}

Checkers :: Checkers(string playerB, string playerR)
	:abstractGame(), isBlacksTurn_(true), currentMoveType_(EMPTY), Bcount_(0), Rcount_(0)
{
	maxSymbol_=1;

	this ->setBoardDim(defaultBoardSize);

	playerB_ = playerB;
	playerR_ = playerR;

	checkerPiece black = checkerPiece(BLACK);
	checkerPiece red = checkerPiece(RED);

	bool offsetLine = false;

	int xOffset;

	for(int i = 0; i < 3; ++i)
	{
		for(int j = 0; j < 4; ++j)
		{
			xOffset = 2*j;
			if(offsetLine)
			{
				++xOffset;
			}

			board_[Point(xOffset, i)] = red;
			++Rcount_;

		}

		offsetLine = (!offsetLine);


	}

	for(int i = 5; i < 8; ++i)
	{
		for(int j = 0; j < 4; ++j)
		{
			xOffset = 2*j;
			if(offsetLine)
			{
				++xOffset;
			}

			board_[Point(xOffset, i)] = black;
			++Bcount_;
		}

		offsetLine = (!offsetLine);
	}
	
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
	state_ = TURNSTART;
	//begin the turn by printing out a useful message and the board.
	prompt();
	print();
	state_ = NEEDPIECE;

	//asks them for a piece to move until one is selected or a command is given
	while(state_ == NEEDPIECE)
	{
		prompt();
		listen();

		if(checkStartSelect())
		{
			state_ = NEEDLOC;
		}
	}

	//ensures that they are ready to be asked to give a destination point.
	if(state_ != NEEDLOC)
	{
		return;
	}

	//asks them for a destination until they give one. 
	while(state_ == NEEDLOC)
	{
		prompt();
		listen();

		if(moveCheck(start_, dest_))
		{
			state_ = PROCESSING;
		}
	}

	//ensures that that all operations in finding location went properly (i.e. they didnt cancel or
	//input anything weird)
	if(state_ != PROCESSING)
	{
		return;
	}

	if(moveCheck(start_, dest_))
	{
		state_ = EXTENDEDTURN;

		//superfluous for it's boolean check function, but used to ensure that the member variable
		//is accurate for the current move and current jummped piece.
		if(jumpedPiece(start_, dest_))
		{
			movePiece();
			removePiece(jumped_);
		}

		while(state_ == EXTENDEDTURN)
		{
			prompt();
			listen();
		}
	}
	else
	{
		return;
	}


}

void Checkers :: prompt()
{
	string name, color;
	if(isBlacksTurn_)
	{
		name = playerB_;
		color = "BLACK";
	}
	else
	{
		name = playerR_;
		color = "RED";
	}

	switch(state_)
	{
	case TURNSTART:
		cout << "Starting " << name << "'s turn. " << endl;
		cout << "Number of Black Pieces: " << Bcount_ << endl;
		cout << "Number of Red Pieces: " << Rcount_ << endl << endl;
		break;
	case NEEDPIECE:
		cout << name << ", please select a piece to move. ";
		break;
	case NEEDLOC:
		cout << name << "'S TURN: " << endl;
		cout << "Moving piece at " << start_ << ". Where would you like to move it?" ;
		cout << "Type 'listmoves' to see the available moves for this piece." << endl;
		break;
	case EXTENDEDTURN:
		cout << "Continuing turn. Moving piece originally located at " << original_ << "." << endl;
		cout << "Piece currently located at " << start_ << ". Where would you like to move it? ";
		cout << "Type 'listmoves' to see the available moves for this pieces. Type 'finished' or 'done' to end your turn. " << endl;
		break;
	default:
		abstractGame :: prompt();

	}
}

void Checkers :: listen()
{
	abstractGame :: listen();
}

endCondition Checkers :: play()
{
	//begins the game by asking for the names of the players.
	if(roughArg1_ != "1" || roughArg2_ != "2")
	{
		getNames(playerB_, playerR_);
	}

	while(notFinished_)
	{
		turn();

		if(done())
		{
			notFinished_ = false;
		}
	}

	return SUCCESS;
}

bool Checkers :: moveCheck(Point start, Point dest)
{
	checkerPiece piece = checkerPiece();
	piece.set(board_.at(start));
	
	bool isValid = false;
	vector<Point> availChoices = possibleLocations(start);

	if(availChoices.size() == 0)
	{
		return isValid;
	}

	for(unsigned int i = 0; i < availChoices.size(); ++i)
	{
		Point temp = availChoices.at(i);

		if(temp.x_ == dest.x_ && temp.y_ == dest.y_)
		{
			isValid=true;
			currentMoveType_ = getMoveType(start, dest);
		}
	}

	return isValid;	
}

bool Checkers :: jumpedPiece(Point start, Point dest)
{

	if(currentMoveType_ == UP || currentMoveType_ == DOWN || currentMoveType_ == EMPTY)
	{
		return false;
	}

	Point ans;

	if(currentMoveType_ == JUMPDOWN)
	{
		if(start.x_ > dest.x_)
		{
			ans = Point(start.x_ - 1, start.y_-1);
		}
		else
		{
			ans = Point(start.x_ + 1, start.y_ -1);
		}
	}
	else 
	{
		if(start.x_ > dest.x_)
		{
			ans = Point(start.x_ - 1, start.y_ + 1);
		}
		else
		{
			ans = Point(start.x_ + 1, start.y_ + 1);
		}
	}

	if(board_.count(ans)==1)
	{
		jumped_ = ans;
		return true;
	}
	else
		return false;
}

bool Checkers :: checkStartSelect()
{
	if(board_.count(start_) == 0)
	{
		return false;
	}
	if(board_.at(start_).color_ == BLACK)
	{
		if(isBlacksTurn_)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if(isBlacksTurn_)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
}

void Checkers :: movePiece()
{
	board_[dest_]=board_.at(start_);
	board_.erase(start_);

	start_ = dest_;

	if(start_.y_ == 0 && isBlacksTurn_ == true)
	{
		board_.at(start_).flip();
	}
	else if(start_.y_ == 7 && isBlacksTurn_ == false)
	{
		board_.at(start_).flip();
	}
	else
		return;
}

void Checkers :: removePiece(Point p)
{
	checkerPiece removed = checkerPiece();
	removed.set(board_.at(p));

	if(removed.color_ == BLACK)
	{
		--Bcount_;
	}
	else
	{
		--Rcount_;
	}

	board_.erase(p);
	
}

vector<Point> Checkers :: possibleLocations(Point p)
{
	vector<Point> ans;

	checkerPiece checker = checkerPiece();
	checker.set(board_.at(p));

	Point ur, ul, dr, dl, urj, ulj, drj, dlj;

	int moveDist=1, jumpDist=2;

	ur =  Point(p.x_ + moveDist, p.y_ + moveDist);
	ul =  Point(p.x_ - moveDist, p.y_ + moveDist);
	dr =  Point(p.x_ + moveDist, p.y_ - moveDist);
	dl =  Point(p.x_ - moveDist, p.y_ - moveDist);

	urj = Point(p.x_ + jumpDist, p.y_ + jumpDist);
	ulj = Point(p.x_ - jumpDist, p.y_ + jumpDist);
	drj = Point(p.x_ + jumpDist, p.y_ - jumpDist);
	dlj = Point(p.x_ - jumpDist, p.y_ - jumpDist);

	if(checker.isKing_ || isBlacksTurn_)
	{
		if(board_.count(dr) == 0)
		{
			ans.push_back(dr);
		}
		if(board_.count(dl) == 0)
		{
			ans.push_back(dl);
		}
		if(board_.count(drj)==0 && jumpedPiece(start_, dest_))
		{
			ans.push_back(drj);
		}
		if(board_.count(dlj)==0 && jumpedPiece(start_, dest_))
		{
			ans.push_back(dlj);
		}
	}

	if(checker.isKing_ || !isBlacksTurn_)
	{
		if(board_.count(ur) == 0)
		{
			ans.push_back(ur);
		}
		if(board_.count(ul) == 0)
		{
			ans.push_back(ul);
		}
		if((board_.count(urj)==0) && jumpedPiece(start_, dest_))
		{
			ans.push_back(urj);
		}
		if((board_.count(ulj))==0 && jumpedPiece(start_, dest_))
		{
			ans.push_back(ulj);
		}
	}

	return ans;
}

moveType Checkers :: getMoveType(Point start, Point dest)
{
	bool sYisBigger = false;
	bool jumpMove = false;
	if(abs(start.x_ - dest.x_) == 2 || abs(start.y_ - dest.y_) == 2)
	{
		jumpMove = true;
	}

	if(start.y_ > dest.y_)
	{
		sYisBigger = true;
	}
	
	if(!sYisBigger)
	{
		if(!jumpMove)
		{
			return UP;
		}
		else
		{
			return JUMPUP;
		}
	}
	else
	{
		if(!jumpMove)
		{
			return DOWN;
		}
		else
		{
			return JUMPDOWN;
		}
	}
}

void Checkers :: createSave()
{
	return;
}

void Checkers :: loadSave()
{
	abstractGame :: loadSave("checkers");
}

void Checkers :: listMoves()
{
	Point p = start_;

	vector<Point> destinations = possibleLocations(p);

	cout << "AVAILABLE MOVES: ";
	movesOut(cout, destinations);
	cout << endl;

	return;
}

void Checkers :: movesOut(ostream& stream, vector<Point> points)
{
	for(unsigned int i = 0; i < points.size(); ++i)
	{
		stream << points.at(i) << "  |  ";
	}
}







//not needed but necessary functions below
void Checkers :: undo()
{
	cout << "No take backs! You can't undo in checkers!!" << endl;
	return;
}