#include "stdafx.h"
#include "gamePiece.h"

using namespace std;

gamePiece::gamePiece()
	:name_(""), symbol_("") {}

bool gamePiece::operator==(const gamePiece& piece)
{
	return((name_==piece.name_) && (symbol_==piece.symbol_));
}


almondPiece::almondPiece()
{
	name_="Almond";
	symbol_="A";
}

numberSquare::numberSquare(int value)
{
	name_="Number Tile";
	value_ = value;
	symbol_ = value;
}

bool numberSquare::operator==(const numberSquare& piece)
{
	return(value_==piece.value_);
}