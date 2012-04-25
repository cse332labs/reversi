//Lab 4 - Nine Almonds and Magic Squares
//Name: Atalie Holman (aholman@go.wustl.edu) and Mason Allen (mrallen@wustl.edu)
// 5-7-12
// magicSquares.cpp

#include "stdafx.h"
#include "magicSquares.h"

using namespace std;

// overloaded constructor that takes in no parameters and calls magicSquares(3, 1). 3 is the default 
// size, 1 is the default lowest value
magicSquares :: magicSquares()
{
	magicSquares(3, 1);
}

//a overloaded constructor that only takes in a size parameter. It uses lowest at value =1 (default)
// calls magicSquares(size, 1);
magicSquares :: magicSquares(int size)
{
	magicSquares(size, 1);
}


//creates a new magicSquares board with size = size and starting at lowest = lowest. It uses the 
// base constructor for abstractGame(). sets turn_ to zero, sets the board size to size and generates
// the tiles starting at the lowest value until the n^2. Sets and stores other values.
magicSquares :: magicSquares(int size, int lowest)
	: abstractGame()
{
	turn_=0;
	this->setBoardDim(size);
	generateTiles(lowest, size);
	maxAxis_ = getLength(boardx_+1);
	state_=NEEDPIECE;
	lowest_=lowest;
}

//creates tiles based off the given low end and size value
void magicSquares :: generateTiles(int lowest, int dim)
{
	numberSquare piece = numberSquare();
	for(int i = lowest; i <= (dim*dim)+lowest-1; ++i)
	{
		piece.setPiece(i);
		availablePieces_.push_back(piece);
	}
}
// sets the board dimensions. 
void magicSquares :: setBoardDim(int n)
{
	boardx_=n;
	boardy_=n;
}

//abstract version of undo(), retreives most recent piece from usedPieces_ (i.e. the most recent move)
// and calls undo(numberSquare piece) on it (below)
void magicSquares :: undo()
{
	undo(usedPieces_.at(usedPieces_.size()-1));
}

//if piece is on the board, remove it and add it to the available pieces (remove it from used pieces). otherwise
// do nothing
void magicSquares :: undo(numberSquare piece)
{
	vector<numberSquare> availUpdate=availablePieces_, usedUpdate;
	
	for(unsigned int i =0; i< usedPieces_.size(); ++i)
	{
		if(usedPieces_.at(i).value_ != piece.value_)
		{
			usedUpdate.push_back(usedPieces_.at(i));
		}
		else
		{
			availUpdate.push_back(usedPieces_.at(i));
			board_.erase(usedPieces_.at(i).key_);
		}
	}

	++turn_;
	availablePieces_=availUpdate;
	usedPieces_=usedUpdate;
	sort(availablePieces_.begin(), availablePieces_.end());

}

// modified version of prompt() that also calls the abstract version in a default switch case
void magicSquares :: prompt()
{
	switch(state_)
	{
		case SETUP:
			cout << "Welcome to Magic Square! Fill a square board with distinct integers such that the n numbers in all rows, all columns, and both diagonals sum to the same constant." << endl << endl;
			cout << "Magic Square can be played on any N x N board. What size board would you like? ";
			listen();
			cout << "Magic Constant = " << getMagicConstant() << endl;
			state_=NEEDPIECE;
			break;
		case NEEDLOC:
			cout << "Where do you want to place that piece? ";
			listen();
			break;
		default:
			abstractGame :: prompt();
	}
}

// returns the magicConstant for this game. 
int magicSquares::getMagicConstant()
{
	int m = (boardx_ * ((boardx_ * boardx_) + 1) ) / 2;
	return m;
}

// print function that inserts the game into the operator<<(game) below
void magicSquares :: print()
{
	cout << *this << endl;
}

//sums up each row and column using helper methods and compares it to the magic constant
// then checks the diagonals. if any of these sums are not equal to the magic constant, return false
// otherwise return true. uses a copy to preserve original
bool magicSquares :: done()
{
	magicSquares copy = *this;
	int m = copy.sumRow(0);

	// makes sure they dont have any pieces left
	if(copy.availablePieces_.size() != 0)
	{
		return false;
	}
	// checks all the rows and columns.
	for(int i = 0; i < copy.boardx_; ++i) 
	{
		if(copy.sumRow(i) != m || copy.sumCol(i) != m)
		{
			return false;
		}
	}
	//sum each diagonal and compare to magic constant
	int sumDiagTopRight = 0;
	int sumDiagTopLeft = 0;
	int j = copy.boardx_-1;
	for(int i = 0; i < copy.boardx_; ++i)
	{
		int right = atoi(copy.board_[Point(i, j)].symbol_.c_str());
		int left = atoi(copy.board_[Point(j, j)].symbol_.c_str());
		sumDiagTopRight += right;
		sumDiagTopLeft += left;
		--j;
	}
	if(sumDiagTopRight != m || sumDiagTopLeft != m)
	{
		return false;
	}
	return true;
}

//helper method for done()
int magicSquares :: sumRow(int r)
{
	int sum = 0;
	for(int i = 0; i <boardx_ ; ++i)
	{
		sum += atoi(board_[Point(i, r)].symbol_.c_str());
	}
	return sum;
}
//helper method for done()
int magicSquares :: sumCol(int r)
{
	int sum =0 ;
	for(int i = 0; i <boardx_ ; ++i)
	{
		sum += atoi(board_[Point(r, i)].symbol_.c_str());
	}
	return sum;
}

// a specialized overload version of prompt() which asks for the tile to be
//placed. calls a specialized version of listen()
void magicSquares :: prompt(unsigned int &piece)
{
	cout << "Which piece do you want to move? ";
	listen(piece);
	if(checkTile(piece))
	{
		state_=NEEDLOC;
	}
	else
	{
		undo(piece);
	}
}

//checks if the tile is already on the board. true if it is not on the board, false if it is
bool magicSquares :: checkTile(int value)
{
	bool ans = false;
	for(unsigned int i = 0; i < availablePieces_.size(); ++i)
	{
		if(availablePieces_.at(i).value_ == value)
		{
			ans = true;
		}
	}
	return ans;
}

// does the turn logic for magicnumbers, makes sure to prompt and update gamestate as needed
void magicSquares :: turn()
{
	if(state_ != NEEDPIECE && state_ !=ENDTURN)
	{
		prompt();
		if(state_ == EXTENDEDTURN)
		{
			pieceAdd(numberSquare(chosenTile_), start_);
			state_=ENDTURN;
		}
	}
	else if(state_==ENDTURN)
	{
		state_=NEEDPIECE;
	}
	else
	{
		prompt(chosenTile_);
	}

}

// listens for a tile type. If the tile is already on the board it calls undo(tile) otherwise 
// it accepts the tile and stores it as chosenTile_ and asks for a location to place it.
void magicSquares :: listen(unsigned int &numberTile)
{
	string input;
	getline (cin, input);

	lowerCase(input);
	istringstream iss(input);
	string in1;
	if(iss >> in1)
	{
		if(!quitGuard_)
		{
			if(in1 == "quit" || in1 == "yes")
			{
				throw QUIT;
			}
			else
				quitGuard_=true;
		}
		if(in1 == "quit")
		{
			if(quitGuard_)
			{
				cout << "Are you sure you want to quit? Type 'yes' to confirm. ";
				quitGuard_=false;
				listen(numberTile);
			}
		}
		bool num1=true;
		char minus = '-';
		for(unsigned int i=0; i<in1.length(); ++i)
		{
			if(!isdigit(in1.at(i)) && in1.at(i) != minus)
			{
				num1 = false;
			}
		}
		if(num1)
		{
			numberTile=atoi(in1.c_str());
		}
	}
	else
		return;

}

//calls generic listen method
void magicSquares :: listen()
{
	abstractGame :: listen();
}

// the required operator overload that takes in a game object and prints out the board (and returns the stream).
// works for NxN boards :-)
ostream& operator<<(ostream &stream, const magicSquares &gamein)
{
    // formatting set-up to account for variable length symbols and for readability 
	magicSquares game = gamein;
    char space = ' ';
	string spacing(game.maxSymbol(), space); // adds space the width of the max length symbol
    int dashCount = (game.boardx_ * (game.maxSymbol_ + 2)) + (game.boardx_ - 1); 
    string dashes(dashCount,'-');
	string offset(game.maxAxis_+1, space); // offets by the width of the vertical axis
    char verticalBar = '|';
    string dashRow = offset + verticalBar + dashes + verticalBar;

	stream << spacing << 'y' << endl;

	for(unsigned int y=(game.boardy_); y > 0; --y)
    {
		stream << dashRow << endl; //add a dashed line before each line of content for formatting

		for(int x=0; x < game.boardx_; ++x)
        { 

			if(x==0 && y!=0) // check if beginning of a new row
            {
                if (getLength(y-1) < (int) game.maxAxis_)
                {
					//determine number spaces to add before y-axis symbol (only need if we are using nxn boards)
                    string spaces(game.maxAxis_ - getLength(y-1), space);
                    stream << spaces;
                }
                stream << y-1; //prints vertical axis
			}


			stream << space << verticalBar << space;
			if(game.board_.count(Point(x, y-1)) == 1) //check if there is a piece at that position
            {
				numberSquare piece = numberSquare(game.board_.at(Point(x, y-1)).value_);

				if (getLength(piece.value_) < game.maxSymbol_) 
                {
					//determine number spaces to add before symbol
					string spaces(game.maxSymbol_ - getLength(piece.value_), space);
					stream << spaces;
				}
				stream << piece.symbol_;
            }
            else
            {
				stream << spacing; 
            }
		}
        stream << space << verticalBar << endl;
	}
    stream << dashRow << endl;
	stream << offset;  // offets the axis labeling by the width of the vertical axis

	//prints the horizontal axis
	for(int xPos=0; xPos < game.boardx_; ++xPos)
	{
		if (getLength(xPos) < game.maxSymbol_)
        {
			//determine number spaces to add before symbol
			string spaces(game.maxSymbol_ - getLength(xPos), space);
			stream << spaces;
		}
		stream << space << space << xPos << space;
	}
	stream << " x" << endl << endl;


    stream << " Available Pieces: " << game.availablePieces_ << endl << endl; 
    return stream;
}

//prints out a list of numberSquare pieces by iterating through and printing out their symbols
ostream& operator<<(ostream &stream, const vector<numberSquare> &pieces)
{
	for(unsigned int i=0; i<pieces.size(); ++i)
	{
		cout << pieces.at(i).symbol_ << " ";
	}
	return stream;
}

// play function that repeatedly checks if the game is done, and if it is not it calls
// turn(). upon finishing it returns SUCCESS
endCondition magicSquares :: play()
{
	bool finished = false;
	while(!finished)
	{
		if(state_ != ENDTURN)
		{
			print();
		}
		turn();
		if(this->done())
		{
			finished=true;
		}
	}
	print();
	cout << "Congratulations! You completed the Magic Square Game of size " << boardx_ << " x " << boardx_ << "." << endl;
	if(turn_ != 0)
	{
		cout << "You made " << turn_ << " undoes/invalid moves while placing the pieces." << endl;
	}
	return SUCCESS;
}

// adds a piece to the board at the location. Used instead of pieceMover for magicSquares
// since magicSquares doesn't have a start point.
void magicSquares :: pieceAdd(numberSquare &piece, Point location)
{
	board_[location]=piece;
	piece.key_=location;
	if(piece.symbol_.size() > (unsigned int) maxSymbol_)
	{
		maxSymbol_=piece.symbol_.size();
	}
	vector<numberSquare> availUpdated;
	for(unsigned int i=0; i<availablePieces_.size(); ++i)
	{
		if(availablePieces_.at(i).value_!=piece.value_)
		{
			availUpdated.push_back(availablePieces_.at(i));
		}
		else
		{
			usedPieces_.push_back(piece);
		}
	}
	availablePieces_=availUpdated;
}

void magicSquares :: createSave()
{
	ofstream save;

	save.open (name_ + ".txt");

	bool finished = false;
	int line = 1;

	while(!finished)
	{
		switch(line)
		{
		case 1:
			save << "magicSquare";
			break;
		case 2:
			save << name_;
			break;
		case 3:
			save << turn_ << " " << state_ << " " << validFirst_ << " " << boardx_ << "," << boardy_;
			break;
		case 4:
			save << start_.x_ << "," << start_.y_ << " " << dest_.x_ << "," <<  dest_.y_;
			break;
		case 5:
			save << chosenTile_ << " " << lowest_ << maxAxis_;
			break;
		case 6:
			for(unsigned int i = 0; i < availablePieces_.size(); ++i)
			{
				save << availablePieces_.at(i).symbol_ << " ";
			}
			cout << endl;
			break;
		case 7:
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
						numberSquare piece = numberSquare(board_.at(temp).value_);

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

void magicSquares :: loadSave()
{
	abstractGame :: loadSave("magicSquares");
}