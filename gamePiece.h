#include "stdafx.h"

#ifndef GAMEPIECE_H
#define GAMEPIECE_H

#include "Point.h"
#include <string>

using namespace std;

//declarations for basic gamepiece
struct gamePiece
{
	string name_;
	string symbol_;

	bool operator==(const gamePiece& piece);

	gamePiece();
};

// the almondpiece has no special variables, but the default constructor knows to assing the proper name and symbol
struct almondPiece : gamePiece
{
	almondPiece();
	bool operator==(const almondPiece& piece);
};

// the numberSquare has an added variable (value_) and a special constructor. 
struct numberSquare : gamePiece
{
	int value_;
	numberSquare(int value);	
	bool operator==(const numberSquare& piece);
};

#endif