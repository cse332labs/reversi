//Lab 5 - Single Player and Multiplayer Games
//Name: Atalie Holman (aholman@go.wustl.edu) and Mason Allen (mrallen@wustl.edu) and Chris Lauber (clauber@wustl.edu)
// 4-27-12
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
	color_ = color;
	
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
	gamePiece :: flip();
}

void numberSquare :: flip()
{
	gamePiece :: flip();
}

void gamePiece :: flip()
{
	return;
}

void reversiPiece :: flip()
{
	if(this->color_ == BLACK)
	{
		name_="White";
		symbol_="O";
		color_ = WHITE;
		value_ = WHITE;
	}
	else
	{
		name_="Black";
		symbol_="X";
		color_ = BLACK;
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

checkerPiece :: checkerPiece()
{
	checkerPiece(BLACK);
}

checkerPiece :: checkerPiece(pieceColor color)
{
	value_ = color;
	color_ = color;
	isKing_ = false;
	switch(color)
	{
	case BLACK:
		name_ = "black checker";
		symbol_="X";
		break;
	case RED:
		name_ = "red checker";
		symbol_="O";
		break;
	default:
		value_=0;
		color_=INVALID_COLOR;
		name_="badpiece";
		symbol_="ERROR:BADPIECE";
		break;
	}
}

void checkerPiece :: flip()
{
	isKing_ = true;
	if(color_ == RED)
	{
		name_ = "red king";
		value_ = 1337;
		symbol_ = "R";
	}
	else if(color_ == BLACK)
	{
		name_ = "black king";
		value_ = 1337;
		symbol_ = "b";
	}
	else
	{
		isKing_ = false;
		cout << "There was an error trying to king that piece." << endl;
	}
}

void checkerPiece :: king()
{
	flip();
}

void checkerPiece :: set(gamePiece p)
{
	this->color_=p.color_;
	this->name_ = p.name_;
	this->symbol_ = p.symbol_;
	this->value_ = p.value_;
	if(value_ == 1337)
	{
		isKing_ = true;
	}
	else
		isKing_ = false;
	return;
}


