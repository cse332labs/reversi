//Lab 4 - Nine Almonds and Magic Squares
//Name: Atalie Holman (aholman@go.wustl.edu) and Mason Allen (mrallen@wustl.edu)
// 5-7-12
// gamePiece.cpp

#include "stdafx.h"
#include "gamePiece.h"

using namespace std;

// default constructor, has no name or symbol
gamePiece::gamePiece()
	:name_(""), symbol_("") {}

// operator to check if symbol and name are the same
bool gamePiece::operator==(const gamePiece& piece)
{
	return((name_==piece.name_) && (symbol_==piece.symbol_));
}

// creates a piece named Almond with symbol A
almondPiece::almondPiece()
{
	name_="Almond";
	symbol_="A";
}

reversiPiece::reversiPiece()
{
	name_="Black";
	symbol_="X";
	value_ = BLACK;
}

reversiPiece::reversiPiece(pieceColor color)
{
	value_ = color;
	
	if(value_ == BLACK)
	{
		name_="Black";
		symbol_="X";
	}
	else if(value_ == WHITE)
	{
		name_="White";
		symbol_="O";
	}
	else //invalid color
	{
		name_="";
		symbol_="";
	}
}

void almondPiece :: flip()
{
	return;
}

void numberSquare :: flip()
{
	return;
}

void gamePiece :: flip()
{

}

void reversiPiece :: flip()
{
	if(TF_ == true)
	{
		name_="White";
		symbol_="O";
		TF_=false;
		value_ = WHITE;
	}
	else
	{
		name_="Black";
		symbol_="X";
		TF_=true;
		value_ = BLACK;
	}
}

//creates a numberSquare named "NumberTile" and sets its variables to value
numberSquare::numberSquare(unsigned int value)
{
	name_="Number Tile";
	setPiece(value);
}

// checks if the value of the two pieces are the same, if they are return true
bool numberSquare::operator==(const numberSquare& piece)
{
	return(value_==piece.value_);
}

// default numberSquare
numberSquare :: numberSquare()
{
	name_ ="Null Tile";
	value_=0;
	symbol_="";
}

// sets the value to n, and the symbol to the string of int n.
void numberSquare :: setPiece(int n)
{

	value_=n;
	stringstream toString;
	toString << n;
	symbol_ = toString.str();
}

//compares numbersquares using their value_ variable and the less than operator. used for sorting.
bool const numberSquare :: operator<(const numberSquare &other) 
{
	return (this->value_ < other.value_);
}