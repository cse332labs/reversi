//Lab 5 - Single Player and Multiplayer Games
//Name: Atalie Holman (aholman@go.wustl.edu) and Mason Allen (mrallen@wustl.edu) and Chris Lauber (clauber@wustl.edu)
// 4-27-12
// nineAlmonds.cpp

#include "stdafx.h"
#include "nineAlmonds.h"

using namespace std;

//constructs nineAlmonds using the base class constructor and its own specifications. fills board
// for proper nine almonds game.
nineAlmonds::nineAlmonds()
	: abstractGame() 
{
	boardx_=5;
	boardy_=5;
	turn_=1;
	almondPiece almond = almondPiece();
	for(int i=0; i < boardx_ ; ++i)
	{
		for(int j=0; j < boardy_; ++j)
		{
			if( ((i<boardx_-1)&&(i>0)) && ((j<boardy_-1)&&(j>0)) )
			{
				Point temp = Point(i, j);
				board_[temp]=almond;
			}
		}
	}
	undoBoards_.push_back(board_);
}

//finds the jumped piece
Point nineAlmonds::jumpedPiece(Point start, Point end)
{
	int jumpedx, jumpedy;

	jumpedx=(start.x_ + end.x_)/2;
	jumpedy=(start.y_ + end.y_)/2;
	return Point(jumpedx, jumpedy);
}

//overridden instance of piecemover that adjusts booleans used in nineAlmonds as well as calls pieceKiller 
//on jumpedPiece. moves piece from board_[start] to board_[destination] if start has a piece and destination
// is empty. Jumped piece must also have a piece. both start and jumped are removed.
bool nineAlmonds :: pieceMover(Point start, Point destination)
{
	Point jumped = jumpedPiece(start, destination);
	if(board_.count(jumped) != 1)
	{
		cout << "You have to jump over an occupied spot on the board. Please select another move." << endl;
		return false;
	}
	else
	{
		almondPiece almond = almondPiece();
		board_.erase(jumped);
		board_[destination] = almond;
		start_=destination;
		board_.erase(start);

		validFirst_=true;
		return true;
	}
}

// undoes moves starting with most recent
void nineAlmonds :: undo()
{
	state_= TURNSTART;
	int i = undoBoards_.size()-1;
	board_=undoBoards_.at(i);
	movesThisTurn_.clear();
	return;
}

// print operator using operator<< below
void nineAlmonds :: print()
{
	cout << *this << endl;
}

// checks if the board is completed, returns true if finished otherwise false.
// finished only if one almond remains and it is in square 2,2
bool nineAlmonds :: done()
{
	bool empty = true;
	Point key = Point();
	for(int i = 0; i <5; ++i)
	{
		for (int j=0; j<5; ++j)
		{
			key.set(i, j);
			if(board_.count(key) == 1 && (i != 2 || j != 2))
				empty = false;
		}
	}
	if(empty && (board_.count(Point(2, 2)) == 1))
	{
		print();
		return true;
	}
	return false;
}

// calls prompt from abstractGame
void nineAlmonds :: prompt()
{
	abstractGame :: prompt();
}

// does the turn logic for nineAlmonds. calls prompt and listen where appropriate.
void nineAlmonds :: turn()
{

	switch(state_)
	{
	case SETUP:
		cout << "Welcome to Nine Almonds!" << endl;
		cout << "Your goal is to remove all almonds except for one, leaving the final almond in the center square (2,2)." << endl;
		cout << "You may make moves by jumping one almond over another, removing the jumped piece. Use a square's coordinate point to select it."<< endl;
		state_=TURNSTART;
		break;
	case FIRSTLOCKED:
		original_ = start_;
		break;
	case EXTENDEDTURN:
		cout << "Continuing turn " << turn_ << ". Originally started moving piece at " << original_ << endl << endl;
		break;
	case ENDTURN:
		++turn_;
		undoBoards_.push_back(board_);
		state_=TURNSTART;
		break;
	}
	if(comingBack_)
	{
		comingBack_=false;
		cout << "Welcome back to Nine Almonds. Rejoining the game on turn " << turn_ << "." << endl;
	}
	print();
	cout << moves_.str() << endl;
	prompt();
	listen();
}

// calls the abstract listen 
void nineAlmonds :: listen()
{
	abstractGame :: listen();
}

//repeatedly calls turn() until done() evaulates true. Then returns SUCCESS.
endCondition nineAlmonds :: play()
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

	cout << "Congratulations! You completed the game in " << turn_ << " turns! Exiting game now." << endl << endl;
	return SUCCESS;
}

//formats a NineAlmonds board for printing.
ostream& operator<<(ostream &stream, const nineAlmonds &game)
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
                                almondPiece almond = almondPiece();
								stream << almond.symbol_;
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

void nineAlmonds :: createSave()
{
	ofstream save;
	// opens the file with the same name as the game being played.
	save.open (name_ + ".txt");
	//identifies the save file at the top
	save << "nineAlmonds" << endl;
	save << name_ << endl;
	// begins to print gamestate. The first line contains the turn #, the gameState_, the validfirst bool, 
	// board diemsions
	save << turn_ << " " << state_ << " " << validFirst_ << " " << boardx_ << "," << boardy_ << endl;
	// the second line has the starting point and destination point
	save << start_.x_ << "," << start_.y_ << " " << dest_.x_ << "," << dest_.y_ << endl;

	save << original_.x_ << "," << original_.y_ << endl;

	save << "BOARD START" << endl;

	for (int i = 0; i < boardx_ ; ++i)
	{
		for ( int j = 0; j < boardx_; ++j)
		{
			if(board_.count(Point(i, j))==1)
			{
				almondPiece almond = almondPiece();
				save << "(" << i << "," << j << ") " << almond.name_ << " " << almond.symbol_ << endl;
			}
		}
	}

	save << "END" << endl;
}

void nineAlmonds :: loadSave()
{
	abstractGame :: loadSave("nineAlmonds");
}



